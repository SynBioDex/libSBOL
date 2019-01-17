/**
 * @file    sequence.h
 * @brief   Sequence class
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include "toplevel.h"

#include <string>

namespace sbol
{
    /// The primary structure (eg, nucleotide or amino acid sequence) of a ComponentDefinition object
	class SBOL_DECLSPEC Sequence : public TopLevel
	{
	public:
        /// Construct a Seqiemce
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param elements A string representation of the primary structure of DNA, RNA, protein, or a SMILES string for small molecules.
        /// @param encoding A URI that describes the representation format used for the elements property. Set to SBOL_ENCODING_IUPAC by default
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string.
        Sequence(std::string uri = "example", std::string elements = "", std::string encoding = SBOL_ENCODING_IUPAC, std::string version = VERSION_STRING) : Sequence(SBOL_SEQUENCE, uri, elements, encoding, version) {};
        
        /// Constructor used for defining extension classes
        /// @param type_uri The RDF type for an extension class derived from this one
        Sequence(rdf_type type_uri, std::string uri, std::string elements, std::string encoding, std::string version) :
            TopLevel(type_uri, uri, version),
            elements(this, SBOL_ELEMENTS, '1', '1', ValidationRules({}), elements),
            encoding(this, SBOL_ENCODING, '1', '1', ValidationRules({}), encoding)
            {
            };
        
        /// The elements property is a REQUIRED String of characters that represents the constituents of a biological or chemical molecule. For example, these characters could represent the nucleotide bases of a molecule of DNA, the amino acid residues of a protein, or the atoms and chemical bonds of a small molecule.
		TextProperty elements;
        
        /// The encoding property is REQUIRED and has a data type of URI. This property MUST indicate how the elements property of a Sequence MUST be formed and interpreted. For example, the elements property of a Sequence with an IUPAC DNA encoding property MUST contain characters that represent nucleotide bases, such as a, t, c, and g. The elements property of a Sequence with a Simplified Molecular-Input Line-Entry System (SMILES) encoding, on the other hand, MUST contain characters that represent atoms and chemical bonds, such as C, N, O, and =.
        /// It is RECOMMENDED that the encoding property contains a URI from the table below. The terms in the table are organized by the type of ComponentDefinition that typically refer to a Sequence with such an encoding.  When the encoding of a Sequence is well described by one of the URIs in the table, it MUST contain that URI.
        /// | ComponentDefinition type  | Encoding       | libSBOL Symbol              | URI                                              |
        /// | :------------------------ | :--------------| :-------------------------- | :----------------------------------------------- |
        /// | DNA, RNA                  | IUPAC DNA, RNA | SBOL_ENCODING_IUPAC         | http://www.chem.qmul.ac.uk/iubmb/misc/naseq.html |
        /// | Protein                   | IUPAC Protein  | SBOL_ENCODING_IUPAC_PROTEIN | http://www.chem.qmul.ac.uk/iupac/AminoAcid/      |
        /// | Small Molecule            | SMILES         | SBOL_ENCODING_SMILES        | http://www.opensmiles.org/opensmiles.html        |
        URIProperty encoding;

        /// Calculates the complete sequence of a high-level Component from the sequence of its subcomponents. Pior to assembling the the complete sequence, you must assemble a template design by calling ComponentDefinition::assemble for the ComponentDefinition that references this Sequence.
        /// @param composite_sequence Typically no value for the composite sequence should be specified by the user. This parameter is used to hold the composite sequence as it is passed to function calls at a higher-level of the recursion stack.
        std::string assemble(std::string composite_sequence = "");

        /// Synonomous with Sequence::assemble. Calculates the complete sequence of a high-level Component from the sequence of its subcomponents. Prior to assembling the the complete sequence, you must assemble a template design by calling ComponentDefinition::assemble for the ComponentDefinition that references this Sequence.
        std::string compile();
        
        /// @return The length of the primary sequence in the elements property
        int length();
        
        /// @param clone_id A URI for the build, or displayId if working in SBOLCompliant mode.
        ComponentDefinition& synthesize(std::string clone_id);
        
        virtual ~Sequence() {};
	};
}

#endif