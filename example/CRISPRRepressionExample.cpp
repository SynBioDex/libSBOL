
#include "sbol.h"

using namespace std;
using namespace sbol;

int main()
{
	setHomespace("http://sys-bio.org");
	Document &doc = *new Document();
	std::string version = "1.0";

	// Create ComponentDefinition for cas9_generic protein
	ComponentDefinition& cas9_generic = *new ComponentDefinition("cas9_generic", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(cas9_generic);

	// Create ComponentDefinition for gRNA_generic RNA
	ComponentDefinition& gRNA_generic = *new ComponentDefinition("gRNA_generic", BIOPAX_RNA, version);
	//gRNA_generic.roles.set(SBO_SGRNA);
	doc.add<ComponentDefinition>(gRNA_generic);

	// Create ComponentDefinition for cas9_gRNA_complex
	ComponentDefinition& cas9_gRNA_complex = *new ComponentDefinition("cas9_gRNA_complex", BIOPAX_COMPLEX, version);
	doc.add<ComponentDefinition>(cas9_gRNA_complex);

	// Create ComponentDefinition for target gene
	ComponentDefinition& target_gene = *new ComponentDefinition("target_gene", BIOPAX_DNA, version);
	doc.add<ComponentDefinition>(target_gene);

	// Create ComponentDefinition for target protein
	ComponentDefinition& target = *new ComponentDefinition("target", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(target);

	// Create ModuleDefinition for CRISPR_Repression_Template	
	ModuleDefinition &CRISPR_Template = *new ModuleDefinition("CRISPR_Template", version);
	doc.add<ModuleDefinition>(CRISPR_Template);

	//Complex Formation Interaction for Cas9m_BFP and gRNA 
	Interaction &Cas9Complex_Formation = CRISPR_Template.interactions.create("Cas9Complex_Formation");
	Cas9Complex_Formation.types.add(SBO_NONCOVALENT_BINDING);

	Participation &cas9_generic_participation = Cas9Complex_Formation.participations.create("cas9_generic");
	cas9_generic_participation.roles.set(SBO_REACTANT);
	cas9_generic.participate(cas9_generic_participation);

	Participation &gRNA_generic_participation = Cas9Complex_Formation.participations.create("gRNA_generic"); 
	gRNA_generic_participation.roles.set(SBO_REACTANT);
	gRNA_generic.participate(gRNA_generic_participation);

	Participation &cas9_gRNA_complex_participation1 = Cas9Complex_Formation.participations.create("cas9_gRNA_complex");
	cas9_gRNA_complex_participation1.roles.set(SBO_PRODUCT);
	cas9_gRNA_complex.participate(cas9_gRNA_complex_participation1);

	// Production of target from target gene
	Interaction &EYFP_production = CRISPR_Template.interactions.create("EYFP_production"); 
	EYFP_production.types.add(SBO_GENETIC_PRODUCTION);

	Participation &target_gene_participation = EYFP_production.participations.create("target_gene"); 
	target_gene_participation.roles.set(SBO_PROMOTER);
	target_gene.participate(target_gene_participation);

	Participation &target_participation = EYFP_production.participations.create("target"); 
	target_participation.roles.set(SBO_PRODUCT);
	target.participate(target_participation);

	// Inhibition of target by cas9m_BFP_gRNA 
	Interaction &target_generic_gene_inhibition = CRISPR_Template.interactions.create("target_generic_gene_inhibition"); 
	target_generic_gene_inhibition.types.add(SBO_INHIBITION);


	Participation &cas9_gRNA_complex_participation = target_generic_gene_inhibition.participations.create("cas9_gRNA_complex");
	cas9_gRNA_complex_participation.roles.set(SBO_INHIBITOR);
	cas9_gRNA_complex.participate(cas9_gRNA_complex_participation);
	
	Participation &cas9_target_gene_participation = target_generic_gene_inhibition.participations.create("target_gene"); 
	cas9_target_gene_participation.roles.set(SBO_PROMOTER);
	cas9_target_gene_participation.participant.set("target_gene");
	target_gene.participate(cas9_target_gene_participation);

	// Create Sequence for CRa_U6 promoter
	std::string CRa_U6_seq_elements ="GGTTTACCGAGCTCTTATTGGTTTTCAAACTTCATTGACTGTGCC" 
										"AAGGTCGGGCAGGAAGAGGGCCTATTTCCCATGATTCCTTCATAT" 
										"TTGCATATACGATACAAGGCTGTTAGAGAGATAATTAGAATTAAT" 
										"TTGACTGTAAACACAAAGATATTAGTACAAAATACGTGACGTAGA" 
										"AAGTAATAATTTCTTGGGTAGTTTGCAGTTTTAAAATTATGTTTT" 
										"AAAATGGACTATCATATGCTTACCGTAACTTGAAATATAGAACCG" 
										"ATCCTCCCATTGGTATATATTATAGAACCGATCCTCCCATTGGCT" 
										"TGTGGAAAGGACGAAACACCGTACCTCATCAGGAACATGTGTTTA" 
										"AGAGCTATGCTGGAAACAGCAGAAATAGCAAGTTTAAATAAGGCT" 
										"AGTCCGTTATCAACTTGAAAAAGTGGCACCGAGTCGGTGCTTTTT" 
										"TTGGTGCGTTTTTATGCTTGTAGTATTGTATAATGTTTTT";
	

	// Create Sequence for gRNA_b coding sequence
	std::string gRNA_b_elements = "AAGGTCGGGCAGGAAGAGGGCCTATTTCCCATGATTCCTTCATAT" 
		"TTGCATATACGATACAAGGCTGTTAGAGAGATAATTAGAATTAAT" 
		"TTGACTGTAAACACAAAGATATTAGTACAAAATACGTGACGTAGA" 
		"AAGTAATAATTTCTTGGGTAGTTTGCAGTTTTAAAATTATGTTTT" 
		"AAAATGGACTATCATATGCTTACCGTAACTTGAAAGTATTTCGAT" 
		"TTCTTGGCTTTATATATCTTGTGGAAAGGACGAAACACCGTACCT" 
		"CATCAGGAACATGTGTTTAAGAGCTATGCTGGAAACAGCAGAAAT" 
		"AGCAAGTTTAAATAAGGCTAGTCCGTTATCAACTTGAAAAAGTGG" 
		"CACCGAGTCGGTGCTTTTTTT";

	// Create Sequence for mKate
	std::string mKate_seq_elements = "TCTAAGGGCGAAGAGCTGATTAAGGAGAACATGCACATGAAGCTG" 
		"TACATGGAGGGCACCGTGAACAACCACCACTTCAAGTGCACATCC" 
		"GAGGGCGAAGGCAAGCCCTACGAGGGCACCCAGACCATGAGAATC" 
		"AAGGTGGTCGAGGGCGGCCCTCTCCCCTTCGCCTTCGACATCCTG" 
		"GCTACCAGCTTCATGTACGGCAGCAAAACCTTCATCAACCACACC" 
		"CAGGGCATCCCCGACTTCTTTAAGCAGTCCTTCCCTGAGGTAAGT" 
		"GGTCCTACCTCATCAGGAACATGTGTTTTAGAGCTAGAAATAGCA" 
		"AGTTAAAATAAGGCTAGTCCGTTATCAACTTGAAAAAGTGGCACC" 
		"GAGTCGGTGCTACTAACTCTCGAGTCTTCTTTTTTTTTTTCACAG" 
		"GGCTTCACATGGGAGAGAGTCACCACATACGAAGACGGGGGCGTG" 
		"CTGACCGCTACCCAGGACACCAGCCTCCAGGACGGCTGCCTCATC" 
		"TACAACGTCAAGATCAGAGGGGTGAACTTCCCATCCAACGGCCCT" 
		"GTGATGCAGAAGAAAACACTCGGCTGGGAGGCCTCCACCGAGATG" 
		"CTGTACCCCGCTGACGGCGGCCTGGAAGGCAGAAGCGACATGGCC" 
		"CTGAAGCTCGTGGGCGGGGGCCACCTGATCTGCAACTTGAAGACC" 
		"ACATACAGATCCAAGAAACCCGCTAAGAACCTCAAGATGCCCGGC" 
		"GTCTACTATGTGGACAGAAGACTGGAAAGAATCAAGGAGGCCGAC" 
		"AAAGAGACCTACGTCGAGCAGCACGAGGTGGCTGTGGCCAGATAC" 
		"TGCG";

		// Create Sequence for CRP_b promoter
		std::string CRP_b_seq_elements = "GCTCCGAATTTCTCGACAGATCTCATGTGATTACGCCAAGCTACG" 
		"GGCGGAGTACTGTCCTCCGAGCGGAGTACTGTCCTCCGAGCGGAG" 
		"TACTGTCCTCCGAGCGGAGTACTGTCCTCCGAGCGGAGTTCTGTC" 
		"CTCCGAGCGGAGACTCTAGATACCTCATCAGGAACATGTTGGAAT" 
		"TCTAGGCGTGTACGGTGGGAGGCCTATATAAGCAGAGCTCGTTTA" 
		"GTGAACCGTCAGATCGCCTCGAGTACCTCATCAGGAACATGTTGG" 
		"ATCCAATTCGACC"; 

	// Create ComponentDefinition for a Constitutive Promoter
	ComponentDefinition& pConst = *new ComponentDefinition("pConst", BIOPAX_DNA, version);
	pConst.roles.set(SBO_PROMOTER);
	doc.add<ComponentDefinition>(pConst);


	// Create ComponentDefinition for cas9m_BFP coding sequence
	ComponentDefinition& cas9m_BFP_cds = *new ComponentDefinition("cas9m_BFP_cds", BIOPAX_DNA, version);
	cas9m_BFP_cds.roles.set(SO_CDS);
	doc.add<ComponentDefinition>(cas9m_BFP_cds);


	// Create ComponentDefinition for cas9m_BFP gene
	ComponentDefinition& cas9m_BFP_gene = *new ComponentDefinition("cas9m_BFP_gene", BIOPAX_DNA, version);
	cas9m_BFP_gene.roles.set(SO_PROMOTER);
	doc.add<ComponentDefinition>(cas9m_BFP_gene);


	SequenceConstraint &cas9m_BFP_gene_constraint = cas9m_BFP_gene.sequenceConstraints.create("cas9m_BFP_gene_constraint");
	cas9m_BFP_gene_constraint.subject.set(pConst.identity.get());
	cas9m_BFP_gene_constraint.object.set(cas9m_BFP_cds.identity.get());
	cas9m_BFP_gene_constraint.restriction.set(SBOL_RESTRICTION_PRECEDES);  

	// Create ComponentDefintion for cas9m_BFP protein
	ComponentDefinition &cas9m_BFP = *new ComponentDefinition("cas9m_BFP", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(cas9m_BFP);


	// Create ComponentDefintion for CRa_U6 promoter
	ComponentDefinition &CRa_U6 = *new ComponentDefinition("CRa_U6", BIOPAX_DNA, version);
	CRa_U6.roles.set(SO_PROMOTER);
	CRa_U6.sequence.set(CRa_U6_seq_elements);
	doc.add<ComponentDefinition>(CRa_U6);

	// Create ComponentDefintion for gRNA_b coding sequence
	ComponentDefinition &gRNA_b_nc = *new ComponentDefinition("gRNA_b_nc", BIOPAX_DNA, version);
	gRNA_b_nc.roles.set(SO_CDS);
	gRNA_b_nc.sequence.set(CRP_b_seq_elements);
	doc.add<ComponentDefinition>(gRNA_b_nc);

	// Create ComponentDefinition for gRNA_b terminator
	ComponentDefinition &gRNA_b_terminator = *new ComponentDefinition("gRNA_b_terminator", BIOPAX_DNA, version);
	gRNA_b_terminator.roles.set(SO_TERMINATOR);
	doc.add<ComponentDefinition>(gRNA_b_terminator);

	// Create ComponentDefinition for gRNA_b gene
	ComponentDefinition &gRNA_b_gene = *new ComponentDefinition("gRNA_b_gene", BIOPAX_DNA, version);
	gRNA_b_gene.roles.set(SO_PROMOTER);
	doc.add<ComponentDefinition>(gRNA_b_gene);

	SequenceConstraint &gRNA_gene_constraint1 = gRNA_b_gene.sequenceConstraints.create("gRNA_gene_constraint1");
	gRNA_gene_constraint1.subject.set(CRa_U6.identity.get());
	gRNA_gene_constraint1.object.set(gRNA_b_nc.identity.get());
	gRNA_gene_constraint1.restriction.set(SBOL_RESTRICTION_PRECEDES);

	SequenceConstraint &gRNA_gene_constraint2 = gRNA_b_gene.sequenceConstraints.create("gRNA_gene_constraint2");
	gRNA_gene_constraint2.subject.set(gRNA_b_nc.identity.get());
	gRNA_gene_constraint2.object.set(gRNA_b_terminator.identity.get());
	gRNA_gene_constraint2.restriction.set(SBOL_RESTRICTION_PRECEDES);

	//Create ComponentDefinition for gRNA_b RNA
	ComponentDefinition &gRNA_b = *new ComponentDefinition("gRNA_b", BIOPAX_RNA, version);
	gRNA_b.roles.set(SO_MISC);  //SO_SGRNA);
	doc.add<ComponentDefinition>(gRNA_b);

	// Create ComponentDefinition for cas9m_BFP gRNA_b complex 
	ComponentDefinition &cas9m_BFP_gRNA_b = *new ComponentDefinition("cas9m_BFP_gRNA_b", BIOPAX_COMPLEX, version);
	//SequenceOntology so = new SequenceOntology();
	//URI sgrna = so.getURIbyName("sgRNA");
	doc.add<ComponentDefinition>(cas9m_BFP_gRNA_b);

	// Create ComponentDefinition for mKate coding sequence
	ComponentDefinition& mKate_cds = *new ComponentDefinition("mKate_cds", BIOPAX_DNA, version);
	mKate_cds.roles.set(SO_CDS);
	mKate_cds.sequence.set(mKate_seq_elements);
	doc.add<ComponentDefinition>(mKate_cds);

	// Create ComponentDefinition for mKate gene
	ComponentDefinition& mKate_gene = *new ComponentDefinition("mKate_gene", BIOPAX_DNA, version);
	mKate_gene.roles.set(SO_PROMOTER);
	doc.add<ComponentDefinition>(mKate_gene);

	SequenceConstraint &mKate_gene_constraint = mKate_gene.sequenceConstraints.create("mKate_gene_constraint");
	mKate_gene_constraint.subject.set(pConst.identity.get());
	mKate_gene_constraint.object.set(mKate_cds.identity.get());
	mKate_gene_constraint.restriction.set(SBOL_RESTRICTION_PRECEDES);

	// Create ComponentDefinition for mKate protein
	ComponentDefinition& mKate = *new ComponentDefinition("mKate", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(mKate);

	// Create ComponentDefinition for Gal4VP16 coding sequence
	ComponentDefinition& Gal4VP16_cds = *new ComponentDefinition("Gal4VP16_cds", BIOPAX_DNA, version);
	Gal4VP16_cds.roles.set(SO_CDS);
	doc.add<ComponentDefinition>(Gal4VP16_cds);

	// Create ComponentDefintion for Gal4VP16 gene
	ComponentDefinition& Gal4VP16_gene = *new ComponentDefinition("Gal4VP16_gene", BIOPAX_DNA, version);
	Gal4VP16_gene.roles.set(SO_PROMOTER);
	doc.add<ComponentDefinition>(Gal4VP16_gene);

	SequenceConstraint &GAL4VP16_gene_constraint = Gal4VP16_gene.sequenceConstraints.create("GAL4VP16_gene_constraint");
	GAL4VP16_gene_constraint.subject.set(pConst.identity.get());
	GAL4VP16_gene_constraint.object.set(Gal4VP16_cds.identity.get());
	GAL4VP16_gene_constraint.restriction.set(SBOL_RESTRICTION_PRECEDES);

	// Create ComponentDefintion for Gal4VP16 protein
	ComponentDefinition& Gal4VP16 = *new ComponentDefinition("Gal4VP16", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(Gal4VP16);

	// Create ComponentDefinition for CRP_b promoter
	ComponentDefinition& CRP_b = *new ComponentDefinition("CRP_b", BIOPAX_DNA, version);
	CRP_b.roles.set(SO_PROMOTER);
	CRP_b.sequence.set(CRP_b_seq_elements);
	doc.add<ComponentDefinition>(CRP_b);

	// Create ComponentDefintiion for EYFP coding sequence
	ComponentDefinition& EYFP_cds = *new ComponentDefinition("EYFP_cds", BIOPAX_DNA, version);
	EYFP_cds.roles.set(SO_CDS);
	doc.add<ComponentDefinition>(EYFP_cds);

	// Create ComponentDefinition for EYFP gene
	ComponentDefinition& EYFP_gene = *new ComponentDefinition("EYFP_gene", BIOPAX_DNA, version);
	EYFP_gene.roles.set(SO_PROMOTER);
	doc.add<ComponentDefinition>(EYFP_gene);

	SequenceConstraint &EYFP_gene_constraint = EYFP_gene.sequenceConstraints.create("EYFP_gene_constraint");
	EYFP_gene_constraint.subject.set(CRP_b.identity.get());
	EYFP_gene_constraint.object.set(EYFP_cds.identity.get());
	EYFP_gene_constraint.restriction.set(SBOL_RESTRICTION_PRECEDES);

	// Create ComponentDefintiion for EYFP protein
	ComponentDefinition& EYFP = *new ComponentDefinition("EYFP", BIOPAX_PROTEIN, version);
	doc.add<ComponentDefinition>(EYFP);

	// Create ModuleDefintion for CRISPR Repression
	ModuleDefinition &CRPb_circuit = *new ModuleDefinition("CRPb_characterization_Circuit", version);
	doc.add<ModuleDefinition>(CRPb_circuit);

	// Create the FunctionalComponents for the ModuleDefinition CRISPR_Repression

	//how to associate CD? cas9m_BFP
	FunctionalComponent &cas9m_BFP_fc = CRPb_circuit.functionalComponents.create("cas9m_BFP");
	cas9m_BFP_fc.definition.set("cas9m_BFP");
	cas9m_BFP_fc.access.set(SBOL_ACCESS_PRIVATE);
	cas9m_BFP_fc.direction.set(SBOL_DIRECTION_NONE);
	cas9m_BFP_fc.version.set(version);

	//how to associate CD? cas9m_BFP_gene
	FunctionalComponent &cas9m_BFP_gene_fc = CRPb_circuit.functionalComponents.create("cas9m_BFP_gene");
	cas9m_BFP_fc.definition.set("cas9m_BFP_gene");
	cas9m_BFP_gene_fc.access.set(SBOL_ACCESS_PRIVATE);
	cas9m_BFP_gene_fc.direction.set(SBOL_DIRECTION_NONE);
	cas9m_BFP_gene_fc.version.set(version);

	//how to associate CD? gRNA_b
	FunctionalComponent &gRNA_b_fc = CRPb_circuit.functionalComponents.create("gRNA_b");
	cas9m_BFP_fc.definition.set("gRNA_b");
	gRNA_b_fc.access.set(SBOL_ACCESS_PRIVATE);
	gRNA_b_fc.direction.set(SBOL_DIRECTION_NONE);
	gRNA_b_fc.version.set(version);
	
	//how to associate CD? gRNA_b_gene
	FunctionalComponent &gRNA_b_gene_fc = CRPb_circuit.functionalComponents.create("gRNA_b_gene");
	cas9m_BFP_fc.definition.set("gRNA_b_gene");
	gRNA_b_gene_fc.access.set(SBOL_ACCESS_PRIVATE);
	gRNA_b_gene_fc.direction.set(SBOL_DIRECTION_NONE);
	gRNA_b_gene_fc.version.set(version);

	//how to associate CD? mKate
	FunctionalComponent &mKate_fc = CRPb_circuit.functionalComponents.create("mKate");
	cas9m_BFP_fc.definition.set("mKate");
	mKate_fc.access.set(SBOL_ACCESS_PRIVATE);
	mKate_fc.direction.set(SBOL_DIRECTION_NONE);
	mKate_fc.version.set(version);
	
	//how to associate CD? mKate_gene
	FunctionalComponent &mKate_gene_fc = CRPb_circuit.functionalComponents.create("mKate_gene");
	cas9m_BFP_fc.definition.set("mKate_gene");
	mKate_gene_fc.access.set(SBOL_ACCESS_PRIVATE);
	mKate_gene_fc.direction.set(SBOL_DIRECTION_NONE);
	mKate_gene_fc.version.set(version);

	//how to associate CD? Gal4VP16
	FunctionalComponent &Gal4VP16_fc = CRPb_circuit.functionalComponents.create("Gal4VP16");
	cas9m_BFP_fc.definition.set("Gal4VP16");
	Gal4VP16_fc.access.set(SBOL_ACCESS_PRIVATE);
	Gal4VP16_fc.direction.set(SBOL_DIRECTION_NONE);
	Gal4VP16_fc.version.set(version);

	//how to associate CD? Gal4VP16_gene
	FunctionalComponent &Gal4VP16_gene_fc = CRPb_circuit.functionalComponents.create("Gal4VP16_gene");
	cas9m_BFP_fc.definition.set("Gal4VP16_gene");
	Gal4VP16_gene_fc.access.set(SBOL_ACCESS_PRIVATE);
	Gal4VP16_gene_fc.direction.set(SBOL_DIRECTION_NONE);
	Gal4VP16_gene_fc.version.set(version);

	//how to associate CD? EYFP
	FunctionalComponent &EYFP_fc = CRPb_circuit.functionalComponents.create("EYFP");
	cas9m_BFP_fc.definition.set("EYFP");
	EYFP_fc.access.set(SBOL_ACCESS_PRIVATE);
	EYFP_fc.direction.set(SBOL_DIRECTION_NONE);
	EYFP_fc.version.set(version);

	//how to associate CD? EYFP_gene
	FunctionalComponent &EYFP_gene_fc = CRPb_circuit.functionalComponents.create("EYFP_gene");
	cas9m_BFP_fc.definition.set("EYFP_gene");
	EYFP_gene_fc.access.set(SBOL_ACCESS_PRIVATE);
	EYFP_gene_fc.direction.set(SBOL_DIRECTION_NONE);
	EYFP_gene_fc.version.set(version);

	//how to associate CD? cas9m_BFP_gRNA_b
	FunctionalComponent &cas9m_BFP_gRNA_b_fc = CRPb_circuit.functionalComponents.create("cas9m_BFP_gRNA_b");
	cas9m_BFP_fc.definition.set("cas9m_BFP_gRNA_b");
	cas9m_BFP_gRNA_b_fc.access.set(SBOL_ACCESS_PRIVATE);
	cas9m_BFP_gRNA_b_fc.direction.set(SBOL_DIRECTION_NONE);
	cas9m_BFP_gRNA_b_fc.version.set(version);

	/* Production of mKate from the mKate gene */
	Interaction &mKate_production = CRPb_circuit.interactions.create("mKate_production"); 
	mKate_production.types.add(SBO_GENETIC_PRODUCTION);

	Participation &mKate_participation = mKate_production.participations.create("mKate");
	mKate_participation.roles.set(SBO_PRODUCT);
	mKate_participation.participant.set("mKate");

	Participation &mKate_gene_participation = mKate_production.participations.create("mKate_gene"); 
	mKate_gene_participation.roles.set(SBO_PROMOTER);
	mKate_gene_participation.participant.set("mKate_gene");

	// Production of GAL4VP16 from the GAL4VP16 gene
	Interaction &GAL4VP16_production = CRPb_circuit.interactions.create("Gal4VP16_production"); 
	GAL4VP16_production.types.add(SBO_GENETIC_PRODUCTION);

	Participation &Gal4VP16_gene_participation = GAL4VP16_production.participations.create("Gal4VP16_gene"); 
	Gal4VP16_gene_participation.roles.set(SBO_PROMOTER);
	Gal4VP16_gene_participation.participant.set("Gal4VP16_gene");

	Participation &Gal4VP16_participation1 = GAL4VP16_production.participations.create("Gal4VP16"); 
	Gal4VP16_participation1.roles.set(SBO_PRODUCT);
	Gal4VP16_participation1.participant.set("Gal4VP16");

	// Production of cas9m_BFP from the cas9m_BFP gene
	Interaction &cas9m_BFP_production = CRPb_circuit.interactions.create("cas9m_BFP_production"); 
	cas9m_BFP_production.types.add(SBO_GENETIC_PRODUCTION);

	Participation &cas9m_BFP_gene_participation = cas9m_BFP_production.participations.create("cas9m_BFP_gene"); 
	cas9m_BFP_gene_participation.roles.set(SBO_PROMOTER);
	cas9m_BFP_gene_participation.participant.set("cas9m_BFP_gene");

	Participation &cas9m_BFP_participation = cas9m_BFP_production.participations.create("cas9m_BFP"); 
	cas9m_BFP_participation.roles.set(SBO_PRODUCT);
	cas9m_BFP_participation.participant.set("cas9m_BFP");

	// Production of gRNA_b from the gRNA_b gene
	Interaction &gRNA_b_production = CRPb_circuit.interactions.create("gRNA_b_production"); 
	gRNA_b_production.types.set(SBO_GENETIC_PRODUCTION);

	Participation &gRNA_b_gene_participation = gRNA_b_production.participations.create("gRNA_b_gene"); 
	gRNA_b_gene_participation.roles.set(SBO_PROMOTER);
	gRNA_b_gene_participation.participant.set("gRNA_b_gene");

	Participation &gRNA_b_participation = gRNA_b_production.participations.create("gRNA_b"); 
	gRNA_b_participation.roles.set(SBO_PRODUCT);
	gRNA_b_participation.participant.set("gRNA_b");

	// Activation of EYFP production by GAL4VP16
	Interaction &EYFP_Activation = CRPb_circuit.interactions.create("EYFP_Activation"); 
	EYFP_Activation.types.set(SBO_STIMULATION);

	Participation &Gal4VP16_participation = EYFP_Activation.participations.create("Gal4VP16"); 
	Gal4VP16_participation.roles.set(SBO_STIMULATOR);
	Gal4VP16_participation.participant.set("Gal4VP16");

	Participation &EYFP_gene_participation = EYFP_Activation.participations.create("EYFP_gene"); 
	EYFP_gene_participation.roles.set(SBO_PROMOTER);
	EYFP_gene_participation.participant.set("EYFP_gene");

	// Degradation of mKate
	Interaction &mKate_deg = CRPb_circuit.interactions.create("mKate_deg"); 
	mKate_deg.types.set(SBO_GENETIC_PRODUCTION); //SBO_DEGRADATION??

	Participation &mKate_participation1 = mKate_deg.participations.create("mKate"); 
	mKate_participation1.roles.set(SBO_REACTANT);
	mKate_participation1.participant.set("mKate");

	// Degradation of GAL4VP16
	Interaction &GAL4VP16_deg = CRPb_circuit.interactions.create("Gal4VP16_deg"); //role: SBO_GENETIC_DEGRADATION
	GAL4VP16_deg.types.set(SBO_GENETIC_PRODUCTION); //SBO_DEGRADATION

	Participation &Gal4VP16_participation2 = GAL4VP16_deg.participations.create("Gal4VP16"); //role: SBO_REACTANT
	Gal4VP16_participation2.roles.set(SBO_REACTANT);
	Gal4VP16_participation2.participant.set("Gal4VP16");

	// Degradation of cas9m_BFP
	Interaction &cas9m_BFP_deg = CRISPR_Template.interactions.create("cas9m_BFP_deg"); //role: SBO_GENETIC_DEGRADATION
	GAL4VP16_deg.types.set(SBO_GENETIC_PRODUCTION);  //SBO_DEGRADATION

	Participation &cas9m_BFP_participation1 = cas9m_BFP_deg.participations.create("cas9m_BFP"); //role: SBO_REACTANT
	cas9m_BFP_participation1.roles.set(SBO_REACTANT);
	cas9m_BFP_participation1.participant.set("cas9m_BFP");

	// Degradation of gRNA_b
	Interaction &gRNA_b_deg = CRISPR_Template.interactions.create("gRNA_b_deg"); //role: SBO_GENETIC_DEGRADATION
	GAL4VP16_deg.types.set(SBO_GENETIC_PRODUCTION); //SBO_DEGRADATION

	Participation &gRNA_b_participation1 = gRNA_b_deg.participations.create("gRNA_b"); //role: SBO_REACTANT
	gRNA_b_participation1.roles.set(SBO_REACTANT);
	gRNA_b_participation1.participant.set("gRNA_b");

	// Degradation of EYFP
	Interaction &EYFP_deg = CRPb_circuit.interactions.create("EYFP_deg"); //role: SBO_GENETIC_DEGRADATION
	GAL4VP16_deg.types.set(SBO_GENETIC_PRODUCTION);  //SBO_DEGRADATION

	Participation &EYFP_participation = EYFP_deg.participations.create("EYFP"); //role: SBO_REACTANT
	EYFP_participation.roles.set(SBO_REACTANT);
	EYFP_participation.participant.set("EYFP");

	// Degradation of cas9m_BFP_gRNA_b
	Interaction &cas9m_BFP_gRNA_b_deg = CRPb_circuit.interactions.create("cas9m_BFP_gRNA_b_deg"); //role: SBO_GENETIC_DEGRADATION
	GAL4VP16_deg.types.set(SBO_GENETIC_PRODUCTION); //SBO_DEGRADATION

	Participation &cas9m_BFP_gRNA_b_participation = cas9m_BFP_gRNA_b_deg.participations.create("cas9m_BFP_gRNA_b"); //role: SBO_REACTANT
	cas9m_BFP_gRNA_b_participation.roles.set(SBO_REACTANT);
	cas9m_BFP_gRNA_b_participation.participant.set("cas9m_BFP_gRNA_b");

	// Create Template Module
	Module &Template_Module = *new Module("Template_Module", version);
	CRPb_circuit.modules.add(Template_Module);
	//CRPb_circuit.assemble(Template_Module);

	// Add MapsTos to Template Module 
	MapsTo &cas9m_BFP_map = Template_Module.mapsTos.create("cas9m_BFP_map");
	cas9m_BFP_map.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
	cas9m_BFP_map.local.set("cas9m_BFP");
	cas9m_BFP_map.remote.set("cas9_generic");

	MapsTo &gRNA_b_map = Template_Module.mapsTos.create("gRNA_b_map");
	gRNA_b_map.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
	gRNA_b_map.local.set("gRNA_b");
	gRNA_b_map.remote.set("gRNA_generic");

	MapsTo &cas9m_BFP_gRNA_map = Template_Module.mapsTos.create("cas9m_BFP_gRNA_map");
	cas9m_BFP_gRNA_map.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
	cas9m_BFP_gRNA_map.local.set("cas9m_BFP_gRNA_b");
	cas9m_BFP_gRNA_map.remote.set("cas9_generic");

	MapsTo &EYFP_map = Template_Module.mapsTos.create("EYFP_map");
	EYFP_map.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
	EYFP_map.local.set("EYFP");
	EYFP_map.remote.set("target");

	MapsTo &EYFP_gene_map = Template_Module.mapsTos.create("EYFP_gene_map");
	EYFP_gene_map.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
	EYFP_gene_map.local.set("EYFP_gene");
	EYFP_gene_map.remote.set("target_gene");
	
	doc.write("example.xml");

}
