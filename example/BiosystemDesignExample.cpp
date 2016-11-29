/// @file BiosystemDesignExample.cpp
/// An example file demonstrating how to define and connect synthetic modules
#include "sbol.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace sbol;

int main()
{
    setHomespace("http://sys-bio.org");
    Document& doc = *new Document();

    ModuleDefinition& NandGate = *new ModuleDefinition("NandGate");
    ModuleDefinition& NotGate = *new ModuleDefinition("NotGate");
    ModuleDefinition& TumorKiller = *new ModuleDefinition("TumorKiller");
    
    doc.add < ModuleDefinition > (NandGate);
    doc.add < ModuleDefinition > (NotGate);
    doc.add < ModuleDefinition > (TumorKiller);
    
    TumorKiller.assemble({ &NotGate, &NandGate });
    
    // Configure the Nand Gate
    ComponentDefinition& TissueMarker = *new ComponentDefinition("TissueMarker", BIOPAX_PROTEIN);
    ComponentDefinition& TumorMarker = *new ComponentDefinition("TumorMarker", BIOPAX_RNA);
    ComponentDefinition& LacI = *new ComponentDefinition("LacI", BIOPAX_PROTEIN);
    doc.add < ComponentDefinition > ({ &TissueMarker, &TumorMarker, &LacI });
    
    FunctionalComponent& nand_input1 = NandGate.setInput(TissueMarker);
    FunctionalComponent& nand_input2 = NandGate.setInput(TumorMarker);
    FunctionalComponent& nand_output = NandGate.setOutput(LacI);
    
    // Configure the Not Gate
    ComponentDefinition& HBax = *new ComponentDefinition("HBax", BIOPAX_PROTEIN);
    doc.add < ComponentDefinition > (HBax);
    
    FunctionalComponent& not_input = NotGate.setInput(LacI);
    FunctionalComponent& not_output = NandGate.setOutput(HBax);

    nand_output.connect(not_input);
    
    // Define internal components in the NAND gate
    ComponentDefinition& Cas9 = *new ComponentDefinition("Cas9", BIOPAX_PROTEIN);
    ComponentDefinition& GuideRNA = *new ComponentDefinition("GuideRNA", BIOPAX_RNA);
    ComponentDefinition& Cas9GuideRNAComplex = *new ComponentDefinition("Cas9GuideRNAComplex", BIOPAX_COMPLEX);
    ComponentDefinition& TargetPromoter = *new ComponentDefinition("TargetPromoter", BIOPAX_DNA);
    ComponentDefinition& TargetGene = *new ComponentDefinition("TargetGene", BIOPAX_DNA);
    ComponentDefinition& TargetProtein = *new ComponentDefinition("TargetProtein", BIOPAX_PROTEIN);
    doc.add< ComponentDefinition > ({ &Cas9, &GuideRNA, &Cas9GuideRNAComplex, &TargetPromoter, &TargetGene,
        &TargetProtein });
    
    Interaction& complex_formation = NandGate.interactions.create("complex_formation");
    Interaction& gene_repression = NandGate.interactions.create("gene_repression");
    Interaction& gene_production = NandGate.interactions.create("gene_production");
    complex_formation.types.add(SBO_NONCOVALENT_BINDING);
    gene_repression.types.add(SBO_INHIBITION);
    gene_production.types.add(SBO_GENETIC_PRODUCTION);
    
    // Complex formation A + B -> AB
    Participation& A = complex_formation.participations.create("A");
    Participation& B = complex_formation.participations.create("B");
    Participation& AB = complex_formation.participations.create("AB");
    A.roles.add(SBO_REACTANT);
    B.roles.add(SBO_REACTANT);
    AB.roles.add(SBO_PRODUCT);
    
    Participation& repressor = complex_formation.participations.create("repressor");
    Participation& repression_target = complex_formation.participations.create("repression_target");
    repressor.roles.add(SBO_INHIBITOR);
    repression_target.roles.add(SBO_PROMOTER);
    
    // Gene production
    Participation& promoter = gene_production.participations.create("promoter");
    Participation& gene = gene_production.participations.create("gene");
    Participation& gene_product = gene_production.participations.create("gene_product");
    promoter.roles.add(SBO_PROMOTER);
    gene.roles.add(SBO_GENE);
    gene_product.roles.add(SBO_PRODUCT);
    
    Cas9.participate(A);
    GuideRNA.participate(B);
    Cas9GuideRNAComplex.participate(AB);
    Cas9GuideRNAComplex.participate(repressor);
    TargetPromoter.participate(repression_target);
    TargetPromoter.participate(promoter);
    TargetGene.participate(gene);
    TargetProtein.participate(gene_product);

    doc.write("module_example.xml");
}
