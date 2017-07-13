#ifndef COMBINATORIALDERIVATION_INCLUDED
#define COMBINATORIALDERIVATION_INCLUDED

#include "partshop.h"

namespace sbol
{
    /// The VariableComponent class can be used to specify a choice of ComponentDefinition objects for any new Component derived from a template Component in the template ComponentDefinition. This specification is made using the class properties variable, variants, variantCollections, and variantDerivations. While the variants, variantCollections, and variantDerivations properties are OPTIONAL, at least one of them MUST NOT be empty
    class SBOL_DECLSPEC VariableComponent : public Identified
    {
        /// The variable property is REQUIRED and MUST contain a URI that refers to a template `Component` in the template `ComponentDefinition`. If the wasDerivedFrom property of a Component refers to this template Component, then the definition property of the derived Component MUST refer to one of the ComponentDefinition objects referred to by the variants property of the VariableComponent. If not, then this definition property MUST either (1) refer to one of the ComponentDefinition objects from a Collection referred to by the variantCollections property of the VariableComponent, or (2) refer to a ComponentDefinition derived from a CombinatorialDerivation referred to by the variantDerivations property of the VariableComponent.
        ReferencedObject variable;
        
        /// The `repeat` property is REQUIRED and has a data type of URI. This property specifies how many `Component` objects can be derived from the template `Component` during the derivation of a new `ComponentDefinition`. The URI value of this property MUST come from the REQUIRED `operator` URIs provided in the table below
        /// | Operator URI                   | Description |
        /// |-----------------------------------|-------------|
        /// | http://sbols.org/v2#zeroOrOne | No more than one `Component` in the derived `ComponentDefinition` SHOULD have a `wasDerivedFrom` property that refers to the template `Component`. |
        /// | http://sbols.org/v2#one   | Exactly one `Component` in the derived `ComponentDefinition` SHOULD have a `wasDerivedFrom` property that refers to the template `Component`. |
        /// | http://sbols.org/v2#zeroOrMore | Any number of `Component` objects in the derived `ComponentDefinition` MAY have `wasDerivedFrom` properties that refer to the template `Component`.  |
        /// | http://sbols.org/v2#oneOrMore | At least one `Component` in the derived `ComponentDefinition` SHOULD have a `wasDerivedFrom` property that refers to the template `Component`. |
        URIProperty repeat;
        
        /// The variants property is OPTIONAL and MAY contain zero or more URIs that each refer to a ComponentDefinition. This property specifies individual ComponentDefinition objects to serve as options when deriving a new Component from the template Component.
        ReferencedObject variants;
        
        /// The variantCollections property is OPTIONAL and MAY contain zero or more URIs that each refer to a Collection. The members property of each Collection referred to in this way MUST NOT be empty and MUST refer only to ComponentDefinition objects. This property enables the convenient specification of existing groups of ComponentDefinition objects to serve as options when deriving a new Component from the template Component.
        ReferencedObject variantCollections;
        
        /// The variantDerivations property is OPTIONAL and MAY contain zero or more URIs that each refer to a CombinatorialDerivation. This property enables the convenient specification of ComponentDefinition objects derived in accordance with another CombinatorialDerivation to serve as options when deriving a new Component from the template Component. The variantDerivations property of a VariableComponent MUST NOT refer to the CombinatorialDerivation that contains this VariableComponent (no cyclic derivations are allowed
        ReferencedObject variantDerivations;
        
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param repeat A URI indicating how many `Component` objects can be derived from the template `Component`
        VariableComponent(std::string uri = DEFAULT_NS "/VariableComponent/example", std::string repeat = "http://sbols.org/v2#one", std::string version = "1.0.0") : VariableComponent(SBOL_VARIABLE_COMPONENT, uri, repeat, version) {};
        
        VariableComponent(sbol_type type, std::string uri, std::string repeat, std::string version) :
            Identified(type, uri, version),
            variable(SBOL_VARIABLE, SBOL_COMPONENT, this),
            repeat(SBOL_OPERATOR, this),
            variants(SBOL_VARIANTS, SBOL_COMPONENT_DEFINITION, this),
            variantCollections(SBOL_VARIANT_COLLECTIONS, SBOL_COLLECTION, this),
            variantDerivations(SBOL_VARIANT_DERIVATIONS, SBOL_COMBINATORIAL_DERIVATION, this)
        {
        };
    };
    
    /// A ComponentDeriviation specifies the composition of a combinatorial design or variant library for common use cases in synthetic biology, such as tuning the performance of a genetic circuit or biosynthetic pathway through combinatorial DNA assembly and screening
    class SBOL_DECLSPEC CombinatorialDerivation : public TopLevel
    {
    public:
        /// The `strategy` property is OPTIONAL and has a data type of URI. Table 1 provides a list of REQUIRED strategy URIs. If the `strategy` property is not empty, then it MUST contain a URI from Table 1. This property recommends how many `ComponentDefinition` objects a user SHOULD derive from the `template` `ComponentDefinition`.
        /// | Strategy URI                   | Description |
        /// |-----------------------------------|-------------|
        /// | http://sbols.org/v2#enumerate | A user SHOULD derive all `ComponentDefinition` objects with a unique substructure as specified by the `Component` objects contained by the `template` `ComponentDefinition` and the `VariableComponent` objects contained by the `CombinatorialDerivation`. |
        /// | http://sbols.org/v2#sample    | A user SHOULD derive a subset of all `ComponentDefinition` objects with a unique substructure as specified by the `Component` objects contained by the `template` `ComponentDefinition` and the `VariableComponent` objects contained by the `CombinatorialDerivation`. The manner in which this subset is chosen is for the user to decide. |
        URIProperty strategy;
        
        /// The `master` property is REQUIRED and MUST contain a URI that refers to a ComponentDefinition. This ComponentDefinition is expected to serve as a template for the derivation of new ComponentDefinition objects. Consequently, its components property SHOULD contain one or more Component objects that describe its substructure (referred to hereafter as template Component objects), and its sequenceConstraints property MAY also contain one or more SequenceConstraint objects that constrain this substructure.
        ReferencedObject masterTemplate;
        
        /// VariableComponent objects denote the choices available when deriving the library of variants specified by a CombinatorialDerivation
        List < OwnedObject < VariableComponent > > variableComponents;
        
        
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param strategy A URI indicating SBOL_ENUMERATE or SBOL_SAMPLE
        CombinatorialDerivation(std::string uri = DEFAULT_NS "/CombinatorialDerivation/example", std::string strategy = "http://sbols.org/v2#enumerate", std::string version = "1.0.0") : CombinatorialDerivation(SBOL_COMBINATORIAL_DERIVATION, uri, strategy, version) {};
        
        CombinatorialDerivation(sbol_type type, std::string uri, std::string strategy, std::string version) :
            TopLevel(type, uri, version),
            strategy(SBOL_STRATEGY, this),
            masterTemplate(SBOL_TEMPLATE, SBOL_COMBINATORIAL_DERIVATION, this),
            variableComponents(SBOL_VARIABLE_COMPONENTS, this)
        {
        };
    };
    
}

#endif