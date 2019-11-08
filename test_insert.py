import unittest

import sbol
import insert


class TestInsert(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        sbol.setHomespace('https://example.com')

    def makeInsert(self, dst_seq, insert_seq, insert_loc):
        doc = sbol.Document()
        cd0 = sbol.ComponentDefinition('wt_cd')
        cd0.sequence = sbol.Sequence('wt_seq', dst_seq)
        doc.addComponentDefinition(cd0)

        insert_cd = sbol.ComponentDefinition('insert_cd')
        insert_cd.sequence = sbol.Sequence('insert_seq', insert_seq)
        doc.addComponentDefinition(insert_cd)

        cd = cd0.insert(insert_cd, insert_loc, 'new_cd')

        # Return the doc and URI because we get a Segmentation Fault
        # if we return the cd itself and then try to reference it in
        # any way.
        return doc, cd.identity

    def test_insert_negative(self):
        """Test inserting before the beginning of the sequence with a negative
        location. This should get adjusted to a simple prepending of
        the insertion.

        """
        doc, uri = self.makeInsert('atcg', 'gg', -3)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'ggatcg')

    def test_insert0(self):
        """Test inserting before the beginning of the sequence. Prepending.

        """
        doc, uri = self.makeInsert('atcg', 'gg', 0)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'ggatcg')

    def test_insert1(self):
        """Test inserting at the beginning of the sequence. Prepending.

        """
        doc, uri = self.makeInsert('atcg', 'gg', 1)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'ggatcg')

    def test_insert2(self):
        """Test inserting within the sequence.

        """
        doc, uri = self.makeInsert('atcg', 'gg', 2)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'aggtcg')

    def test_insert3(self):
        """Test inserting within the sequence.

        """
        doc, uri = self.makeInsert('atcg', 'aa', 3)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'ataacg')

    def test_insert4(self):
        """Test inserting one base before the end of the sequence.

        """
        doc, uri = self.makeInsert('atcg', 'aa', 4)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'atcaag')

    def test_insert_n(self):
        """Test appending at the end of the initial sequence.

        """
        doc, uri = self.makeInsert('atcg', 'gg', 5)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'atcggg')

    def test_insert_positive(self):
        """Test appending at a location beyond the end of the initial
        sequence.

        """
        doc, uri = self.makeInsert('atcg', 'gg', 8)
        cd = doc.getComponentDefinition(uri)
        cd.compileInsert()
        self.assertEqual(cd.sequence.elements, 'atcggg')

    def test_empty_cd(self):
        """Test that compileInsert fails with a raised exception when
        preconditions are not met.

        """
        test_cd = sbol.ComponentDefinition('test_cd')
        with self.assertRaises(sbol.InsertionError):
            test_cd.compileInsert()

    def test_cd_with_sequence(self):
        """Test that compileInsert fails when the CD already has a sequence.

        """
        test_cd = sbol.ComponentDefinition('test_cd')
        test_cd.sequence = sbol.Sequence('seq', 'atcg')
        with self.assertRaises(sbol.InsertionError):
            test_cd.compileInsert()
