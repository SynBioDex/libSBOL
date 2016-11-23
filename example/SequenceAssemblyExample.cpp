/// @file
/// An example file showing how to assemble hierachical genetic constructs

/// @code
#define BASE_URI "http://sys-bio.org"

#include "sbol.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace sbol;

int main()
{
    setHomespace(BASE_URI);
    Document& doc = *new Document();

    ComponentDefinition& gene = *new ComponentDefinition("BB0001");
    ComponentDefinition& promoter = *new ComponentDefinition("R0010");
    ComponentDefinition& CDS = *new ComponentDefinition("B0032");
    ComponentDefinition& RBS = *new ComponentDefinition("E0040");
    ComponentDefinition& terminator = *new ComponentDefinition("B0012");

    promoter.roles.set(SO_PROMOTER);
    CDS.roles.set(SO_CDS);
    RBS.roles.set(SO_RBS);
    terminator.roles.set(SO_TERMINATOR);
    
    doc.add<ComponentDefinition>(gene);
    doc.add<ComponentDefinition>(promoter);
    doc.add<ComponentDefinition>(CDS);
    doc.add<ComponentDefinition>(RBS);
    doc.add<ComponentDefinition>(terminator);
    
    gene.assemble({ &promoter, &RBS, &CDS, &terminator});

    Component& first = gene.getFirstComponent();
    cout << first.identity.get() << endl;
    Component& last = gene.getLastComponent();
    cout << last.identity.get() << endl;

    Sequence& promoter_seq = *new Sequence("R0010", "ggctgca");
    Sequence& RBS_seq = *new Sequence("B0032", "aattatataaa");
    Sequence& CDS_seq = *new Sequence("E0040", "atgtaa");
    Sequence& terminator_seq = *new Sequence("B0012", "attcga");
    Sequence& gene_seq = *new Sequence("BB0001");

    doc.add<Sequence>({&promoter_seq, &CDS_seq, &RBS_seq, &terminator_seq, &gene_seq});
    
    promoter.sequence.set(promoter_seq.identity.get());
    CDS.sequence.set(CDS_seq.identity.get());
    RBS.sequence.set(RBS_seq.identity.get());
    terminator.sequence.set(terminator_seq.identity.get());
    gene.sequence.set(gene_seq.identity.get());
    
    gene_seq.assemble();
    
    cout << promoter_seq.elements.get() << endl;
    cout << RBS_seq.elements.get() << endl;
    cout << CDS_seq.elements.get() << endl;
    cout << terminator_seq.elements.get() << endl;
    cout << gene_seq.elements.get() << endl;
}
/// @endcode
