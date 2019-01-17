from sbol import *

setHomespace('http://sys-bio.org')
doc = Document()

gene = ComponentDefinition('gene_example')
promoter = ComponentDefinition('R0010')
CDS = ComponentDefinition('B0032')
RBS = ComponentDefinition('E0040')
terminator = ComponentDefinition('B0012')

promoter.roles = SO_PROMOTER
CDS.roles = SO_CDS
RBS.roles = SO_RBS
terminator.roles = SO_TERMINATOR

doc.addComponentDefinition(gene)
doc.addComponentDefinition(promoter)
doc.addComponentDefinition(CDS)
doc.addComponentDefinition(RBS)
doc.addComponentDefinition(terminator)

gene.assemblePrimaryStructure([ promoter, RBS, CDS, terminator ])

first = gene.getFirstComponent()
print(first.identity)
last = gene.getLastComponent()
print(last.identity)

promoter_seq = Sequence('R0010', 'ggctgca')
RBS_seq = Sequence('B0032', 'aattatataaa')
CDS_seq = Sequence('E0040', "atgtaa")
terminator_seq = Sequence('B0012', 'attcga')
gene_seq = Sequence('BB0001')

doc.addSequence([promoter_seq, CDS_seq, RBS_seq, terminator_seq, gene_seq])

promoter.sequences = promoter_seq.identity
CDS.sequences = CDS_seq.identity
RBS.sequences = RBS_seq.identity
terminator.sequences = terminator_seq.identity
gene.sequences = gene_seq.identity

gene_seq.assemble()

print(promoter_seq.elements)
print(RBS_seq.elements)
print(CDS_seq.elements)
print(terminator_seq.elements)
print(gene_seq.elements)

result = doc.write('gene_cassette.xml')
print(result)
