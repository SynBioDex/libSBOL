
// File: index.xml

// File: classsbol_1_1_collection.xml


%feature("docstring") sbol::Collection "

The Collection class is a class that groups together a set of TopLevel objects
that have something in common.  

Some examples of Collection objects: . Results of a query to find all
ComponentDefinition objects in a repository that function as promoters . A set
of ModuleDefinition objects representing a library of genetic logic gates. . A
ModuleDefinition for a complexdesign, and all of the ModuleDefinition,
ComponentDefinition, Sequence, and Model objects used to provide its full
specification.  
";

%feature("docstring") sbol::Collection::addToDocument "

Add the Collection object to Document
";

%feature("docstring") sbol::Collection::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Collection::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Collection::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Collection::Collection "

Construct a Collection.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
";

%feature("docstring") sbol::Collection::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Collection::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Collection::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::Collection::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Collection::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Collection::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

// File: classsbol_1_1_component.xml


%feature("docstring") sbol::Component "

The Component class is used to compose ComponentDefinition objects into a
structural hierarchy. For example, the ComponentDefinition of a gene could
contain four Component objects: a promoter, RBS, CDS, and terminator. In turn,
the ComponentDefinition of the promoter Component could contain Component
objects defined as various operator sites.  
";

%feature("docstring") sbol::Component::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Component::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Component::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Component::copy "
";

%feature("docstring") sbol::Component::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Component::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Component::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Component::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Component::Component "

Construct a Component.  

If operating in SBOL-compliant mode, use ComponentDefinition::components::create
instead.  

Parameters
----------
* `A` :  
    full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `definition` :  
    A URI referring to the ComponentDefinition that defines this instance  
* `access` :  
    Flag indicating whether the Component can be referred to remotely by a
    MapsTo  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::Component::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_component_definition.xml


%feature("docstring") sbol::ComponentDefinition "

The ComponentDefinition class represents the structural entities of a biological
design.  

The primary usage of this class is to represent structural entities with
designed sequences, such as DNA, RNA, and proteins, but it can also be used to
represent any other entity that is part of a design, such as small molecules,
proteins, and complexes
";

%feature("docstring") sbol::ComponentDefinition::participate "

A convenience method that assigns a component to participate in a biochemical
reaction.  

Behind the scenes, it auto-constructs a FunctionalComponent for this
ComponentDefinition and assigns it to a Participation  

Parameters
----------
* `species` :  
    A Participation object (ie, participant species in a biochemical
    Interaction).  
";

%feature("docstring") sbol::ComponentDefinition::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::ComponentDefinition::getLastComponent "

Gets the last Component in a linear sequence.  

Returns
-------
The last component in sequential order  
";

%feature("docstring") sbol::ComponentDefinition::hasDownstreamComponent "

Checks if the specified Component has a Component downstream in linear
arrangement on the DNA strand.  

Checks that the appropriate SequenceConstraint exists.  

Parameters
----------
* `current_component` :  
    A Component in this ComponentDefinition  

Returns
-------
1 if found, 0 if not  
";

%feature("docstring") sbol::ComponentDefinition::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentDefinition::getUpstreamComponent "

Get the upstream Component.  

Returns
-------
The upstream component  
";

%feature("docstring") sbol::ComponentDefinition::updateSequence "

Assemble a parent ComponentDefinition's Sequence from its subcomponent
Sequences.  

Parameters
----------
* `composite_sequence` :  
    A recursive parameter, use default value  

Returns
-------
The assembled parent sequence  
";

%feature("docstring") sbol::ComponentDefinition::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ComponentDefinition::hasUpstreamComponent "

Checks if the specified Component has a Component upstream in linear arrangement
on the DNA strand.  

Checks that the appropriate SequenceConstraint exists.  

Parameters
----------
* `current_component` :  
    A Component in this ComponentDefinition  

Returns
-------
1 if found, 0 if not  
";

%feature("docstring") sbol::ComponentDefinition::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentDefinition::assemble "

Assembles the provided vector of Components into a structural hierarchy.  

update SequenceAnnotation starts and ends  

Autoconstructs the required Components and SequenceConstraints. The resulting
data structure is a partial design, still lacking a specific DNA (or other)
sequence. To fully realize a design, use Sequence::assemble().  

Parameters
----------
* `list_of_components` :  
    A list of subcomponents that will compose this ComponentDefinition  
";

%feature("docstring") sbol::ComponentDefinition::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ComponentDefinition::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::ComponentDefinition::addToDocument "

Add the ComponentDefinition object to Document
";

%feature("docstring") sbol::ComponentDefinition::getInSequentialOrder "

Orders this ComponentDefinition's member Components into a linear arrangement
based on Sequence Constraints.  

Returns
-------
Primary sequence structure  
";

%feature("docstring") sbol::ComponentDefinition::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ComponentDefinition::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ComponentDefinition::getDownstreamComponent "

Get the downstream Component.  

Returns
-------
The downstream component  
";

%feature("docstring") sbol::ComponentDefinition::getFirstComponent "

Gets the first Component in a linear sequence.  

Returns
-------
The first component in sequential order  
";

%feature("docstring") sbol::ComponentDefinition::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::ComponentDefinition::ComponentDefinition "

Construct a ComponentDefinition.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `type` :  
    A BioPAX ontology term that indicates whether the ComponentDefinition is
    DNA, RNA, protein, or some other molecule type.  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

// File: classsbol_1_1_component_instance.xml


%feature("docstring") sbol::ComponentInstance "
";

%feature("docstring") sbol::ComponentInstance::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ComponentInstance::copy "
";

%feature("docstring") sbol::ComponentInstance::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentInstance::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";


%feature("docstring") sbol::ComponentInstance::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::ComponentInstance::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::ComponentInstance::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ComponentInstance::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentInstance::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_config.xml


%feature("docstring") sbol::Config "

A class which contains global configuration variables for the libSBOL
environment. Intended to be used like a static class, configuration variables
are accessed through the `Config' object.
";

%feature("docstring") sbol::Config::setOption "

Configure options for online validation and conversion
Option  

Description  

Values  

validate  

Enable validation and conversion requests through the online validator  

True or False  

validatorURL  

The http request endpoint for validation  

A valid URL, set to  http://www.async.ece.utah.edu/sbol-validator/endpoint.php
by default  

output  

File format for conversion  

SBOL2, SBOL1, FASTA, GenBank  

diff  

Report differences between two files  

True or False  

noncompliantUrisAllowed  

If set to false, URIs in the file will not be checked for compliance  
with the SBOL specification  

True or False  

incompleteDocumentsAllowed  

If set to false, not all referenced objects must be described within  
the given main_file  

True or False  

bestPracticesCheck  

If set to true, the file is checked for the best practice rules set  
in the SBOL specification  

True or False  

failOnFirstError  

If set to true, the validator will fail at the first error  

True or False  

displayFullErrorStackTrace  

If set to true (and failOnFirstError is true) the validator will  
provide a stack trace for the first validation error  

True or False  

topLevelToConvert  



uriPrefix  

Required for conversion from FASTA and GenBank to SBOL1 or SBOL2,  
used to generate URIs  

True or False  

version  

Adds the version to all URIs and to the document  

A valid Maven version string  

wantFileBack  

Whether or not to return the file contents as a string  

True or False  

Parameters
----------
* `option` :  
    The option key  
* `value` :  
    The option value  
";

%feature("docstring") sbol::Config::Config "
";

%feature("docstring") sbol::Config::getOption "

Get current option value for online validation and conversion.  

Parameters
----------
* `option` :  
    The option key  
";

// File: classsbol_1_1_cut.xml


%feature("docstring") sbol::Cut "

The Cut class specifies a location between two coordinates of a Sequence's
elements. 
";

%feature("docstring") sbol::Cut::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Cut::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Cut::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Cut::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Cut::copy "
";

%feature("docstring") sbol::Cut::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Cut::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Cut::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Cut::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Cut::Cut "

Construct a Cut.  

If operating in SBOL-compliant mode, use SequenceAnnotation.locations.create instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
* `at` :  
    An integer of 0 or greater  
";

// File: classsbol_1_1_document.xml


%feature("docstring") sbol::Document "

Read and write SBOL using a Document class. The Document is a container for
Components, Modules, and all other SBOLObjects.  
";

%feature("docstring") sbol::Document::addComponentDefinition "

Adds a component definition or a list of component definitions to a sbol::Document object.

Parameters
----------
* `componentDefinition` : 
    ComponentDefinition object or a list of ComponentDefinition objects
";

%feature("docstring") sbol::Document::addSequence "

Adds a sequence or a list of sequences to a sbol::Document object.

Parameters
----------
* `sequence` : 
    Sequence object or a list of Sequence objects
";

%feature("docstring") sbol::Document::addModuleDefinition "

Adds a module definition or a list of module definitions to a sbol::Document object.

Parameters
----------
* `moduleDefinition` : 
    ModuleDefinition object or a list of ModuleDefinition objects
";

%feature("docstring") sbol::Document::request_validation "

Submit this Document to the online validator.  

Returns
-------
The validation results  
";

%feature("docstring") sbol::Document::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Document::Document "

Construct a Document. The Document is a container for Components, Modules, and
all other SBOLObjects.  
";

%feature("docstring") sbol::Document::add "

Register an object in the Document.  

Parameters
----------
* `sbol_objects` :  
    A list of pointers to the SBOL objects you want to serialize  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object  
";

%feature("docstring") sbol::Document::write "

Serialize all objects in this Document to an RDF/XML file.  

Parameters
----------
* `filename` :  
    The full name of the file you want to write (including file extension)  

Returns
-------
A string with the validation results, or empty string if validation is disabled  
";

%feature("docstring") sbol::Document::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Document::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Document::validate "

Run validation on this Document.  

Returns
-------
The validation results  
";

%feature("docstring") sbol::Document::read "

Read an RDF/XML file and attach the SBOL objects to this Document.  

Existing contents of the Document will be wiped.  

Parameters
----------
* `filename` :  
    The full name of the file you want to read (including file extension)  
";

%feature("docstring") sbol::Document::addNamespace "

Add a new namespace to this Document.  

Parameters
----------
* `ns` :  
    The namespace, eg. http://sbols.org/v2#  
* `prefix` :  
    The namespace prefix, eg. sbol  
";

%feature("docstring") sbol::Document::getAll "

Retrieve a vector of objects from the Document.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL objects  
";

%feature("docstring") sbol::Document::find "

Search recursively for an SBOLObject in this Document that matches the uri.  

Parameters
----------
* `uri` :  
    The identity of the object to search for  

Returns
-------
A pointer to the SBOLObject, or NULL if an object with this identity doesn't
exist  
";

%feature("docstring") sbol::Document::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Document::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Document::getNamespaces "

Returns
-------
A vector of namespaces Get namespaces contained in this Document  
";

%feature("docstring") sbol::Document::append "

Read an RDF/XML file and attach the SBOL objects to this Document.  

New objects will be added to the existing contents of the Document  

Parameters
----------
* `filename` :  
    The full name of the file you want to read (including file extension)  
";

%feature("docstring") sbol::Document::get "

Retrieve an object from the Document.  

Parameters
----------
* `uri` :  
    The identity of the SBOL object you want to retrieve  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object  
";

%feature("docstring") sbol::Document::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Document::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_functional_component.xml


%feature("docstring") sbol::FunctionalComponent "

The FunctionalComponent class is used to specify the functional usage of a
ComponentDefinition inside a ModuleDefinition. The ModuleDefinition describes
how the that describes how the FunctionalComponent interacts with others and
summarizes their aggregate function.  
";

%feature("docstring") sbol::FunctionalComponent::isMasked "

Used to tell if a FunctionalComponent is linked to an equivalent
FunctionalComponent in another ModuleDefinition.  

Returns
-------
1 if the FunctionalComponent has been over-rided by another FunctionalComponent,
0 if it hasn't.  
";

%feature("docstring") sbol::FunctionalComponent::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::FunctionalComponent::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::FunctionalComponent::copy "
";

%feature("docstring") sbol::FunctionalComponent::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::FunctionalComponent::connect "

This method connects module inputs and outputs.  

This convenience method auto-constructs a MapsTo object. See Biosystem Design
for an example  

Parameters
----------
* `interface_component` :  
    An input or output component from another ModuleDefinition that corresponds
    with this component.  
";

%feature("docstring") sbol::FunctionalComponent::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::FunctionalComponent::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::FunctionalComponent::FunctionalComponent "

Construct a FunctionalComponent.  

If operating in SBOL-compliant mode, use
ModuleDefinition::functionalComponents::create instead.  

Parameters
----------
* `A` :  
    full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `definition` :  
    A URI referring to the ComponentDefinition that defines this instance  
* `access` :  
    Flag indicating whether the FunctionalComponent can be referred to remotely
    by a MapsTo  
* `direction` :  
    The direction property specifies whether a FunctionalComponent serves as an
    input, output, both, or neither for its parent ModuleDefinition object  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::FunctionalComponent::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::FunctionalComponent::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::FunctionalComponent::mask "

This method is used to state that FunctionalComponents in separate
ModuleDefinitions are functionally equivalent.  

Using this method will override the FunctionalComponent in the argument with the
FunctionalComponent calling the method. This is useful for overriding a generic,
template component with an explicitly defined component. This convenience method
auto-constructs a MapsTo object. See Biosystem Design for an example  

Parameters
----------
* `masked_component` :  
    The FunctionalComponent that is being masked (over-ridden)  
";

%feature("docstring") sbol::FunctionalComponent::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_generic_location.xml


%feature("docstring") sbol::GenericLocation "

the GenericLocation class is included as a starting point for specifying regions
on Sequence objects with encoding properties other than IUPAC and potentially
nonlinear structure. This class can also be used to set the orientation of a
SequenceAnnotation and any associated Component when their parent
ComponentDefinition is a partial design that lacks a Sequence.  
";

%feature("docstring") sbol::GenericLocation::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::GenericLocation::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GenericLocation::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::GenericLocation::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::GenericLocation::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GenericLocation::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::GenericLocation::copy "
";

%feature("docstring") sbol::GenericLocation::GenericLocation "

Construct a GenericLocation.  

If operating in SBOL-compliant mode, use SequenceAnnotation.locations.create instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
";

%feature("docstring") sbol::GenericLocation::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::GenericLocation::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_identified.xml


%feature("docstring") sbol::Identified "

All SBOL-defined classes are directly or indirectly derived from the Identified
abstract class.  

An Identified object is identified using a Uniform Resource Identifier (URI), a
unique string that identifies and refers to a specific object in an SBOL
document or in an online resource such as a DNA repository.  
";

%feature("docstring") sbol::Identified::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Identified::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Identified::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Identified::copy "
";

%feature("docstring") sbol::Identified::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Identified::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Identified::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Identified::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Identified::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

// File: classsbol_1_1_interaction.xml


%feature("docstring") sbol::Interaction "

The Interaction class provides more detailed descriptionof how the
FunctionalComponents are intended to work together. For example, this class can
be used to represent different forms of genetic regulation (e.g.,
transcriptional activation or repression), processes from the central dogma of
biology (e.g. transcription and translation), and other basic molecular
interactions (e.g., non-covalent binding or enzymatic phosphorylation).  
";

%feature("docstring") sbol::Interaction::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Interaction::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Interaction::copy "
";

%feature("docstring") sbol::Interaction::Interaction "

Construct an Interaction.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `interaction_type` :  
    A Systems Biology Ontology term that describes a biochemical interaction  
";

%feature("docstring") sbol::Interaction::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Interaction::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Interaction::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Interaction::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Interaction::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Interaction::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_int_property.xml


%feature("docstring") sbol::IntProperty "

IntProperty objects are used to contain integers.  

They can be used as member objects inside custom SBOL Extension classes.  
";

%feature("docstring") sbol::IntProperty::IntProperty "
";

%feature("docstring") sbol::IntProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
An integer  
";

%feature("docstring") sbol::IntProperty::getOwner "
";

%feature("docstring") sbol::IntProperty::clear "

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::IntProperty::getAll "

Retrieve a vector of objects from the IntProperty.

";

%feature("docstring") sbol::IntProperty::write "
";

%feature("docstring") sbol::IntProperty::set "

Basic setter for SBOL IntProperty.

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::IntProperty::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

// File: classsbol_1_1_referenced_object_1_1iterator.xml


%feature("docstring") sbol::ReferencedObject::iterator "

Provides iterator functionality for SBOL properties that contain multiple
references.  
";


// File: classsbol_1_1_owned_object_1_1iterator.xml


%feature("docstring") sbol::OwnedObject::iterator "

Provides iterator functionality for SBOL properties that contain multiple
objects.  
";

%feature("docstring") sbol::OwnedObject::iterator::iterator "
";

// File: classsbol_1_1_property_1_1iterator.xml


%feature("docstring") sbol::Property::iterator "

Provides iterator functionality for SBOL properties that contain multiple
values.  
";

%feature("docstring") sbol::Property::iterator::iterator "
";

// File: classsbol_1_1_list.xml


%feature("docstring") sbol::List "

Provides interface for an SBOL container Property that is allowed to have more
than one object or value.  

templateparam
-------------
* `PropertyType` :  
    The type of SBOL Property, eg, Text, Int, OwnedObject, etc  
";

%feature("docstring") sbol::List::List "
";

// File: classsbol_1_1_location.xml


%feature("docstring") sbol::Location "

The Location class specifies the strand orientation of a Component and can be
further extended by the Range, Cut, and GenericLocation classes.  
";

%feature("docstring") sbol::Location::copy "
";

%feature("docstring") sbol::Location::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Location::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Location::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Location::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Location::Location "
";

%feature("docstring") sbol::Location::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Location::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Location::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Location::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_maps_to.xml


%feature("docstring") sbol::MapsTo "

The purpose of the MapsTo class is to make identity relationships between
different ComponentInstances in functional and structural hierarchies more
clear. For example, a MapsTo object may be used to connect outputs and inputs
between different low-level ModuleDefinitions contained in a higher level Module
Definition. A MapsTo object may also be used to override a generic Component in
a low-level ModuleDefinition with an explicit Component in a high-level
ModuleDefinition, for example mapping a generic gene to an explicit component
with a name and sequence.  
";

%feature("docstring") sbol::MapsTo::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::MapsTo::copy "
";

%feature("docstring") sbol::MapsTo::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::MapsTo::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::MapsTo::MapsTo "

Construct a MapsTo.  

If operating in SBOL-compliant mode, use ModuleDefinition::mapsTos::create
instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
* `local` :  
    The identity of the lower level ComponentInstance  
* `remote` :  
    The identity of the higher level ComponentInstance  
* `restriction` :  
    Flag indicating the relationship between high- and low-level
    ComponentInstances. By default, this is set to
    SBOL_REFINEMENT_VERIFY_IDENTICAL  
";

%feature("docstring") sbol::MapsTo::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::MapsTo::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::MapsTo::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::MapsTo::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::MapsTo::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_model.xml


%feature("docstring") sbol::Model "

The purpose of the Model class is to serve as a placeholder for an external
computational model and provide additional meta-data to enable better reasoning
about the contents of this model.  

In this way, there is minimal duplication of standardization efforts and users
of SBOL can formalize the function of a ModuleDefinition in the language of
their choice.  
";

%feature("docstring") sbol::Model::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Model::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Model::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Model::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Model::addToDocument "
Add the Model object to Document
";

%feature("docstring") sbol::Model::Model "
";

%feature("docstring") sbol::Model::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Model::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Model::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Model::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Model::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";


// File: classsbol_1_1_module.xml


%feature("docstring") sbol::Module "

The Module class represents a submodule of a ModuleDefinition within a
hierarchical design.  
";

%feature("docstring") sbol::Module::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Module::Module "

Construct a Module.  

If operating in SBOL-compliant mode, use ModuleDefinition::modules::create
instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
* `definition` :  
    The identity of the Component with this structural constraint  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::Module::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Module::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Module::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Module::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Module::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Module::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Module::copy "
";

%feature("docstring") sbol::Module::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

// File: classsbol_1_1_module_definition.xml


%feature("docstring") sbol::ModuleDefinition "

The ModuleDefinition class represents a grouping of structural and functional
entities in a biological design. The primary usage of this class is to assert
the molecular interactions and abstract function of its child entities.  
";

%feature("docstring") sbol::ModuleDefinition::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::ModuleDefinition::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ModuleDefinition::assemble "

Assemble a high-level ModuleDefinition from lower-level submodules.  

Autoconstructs Module objects in the process.  

Parameters
----------
* `list_of_modules` :  
    A list of pointers to the submodule ModuleDefinitions  
";

%feature("docstring") sbol::ModuleDefinition::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ModuleDefinition::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ModuleDefinition::setInput "

Defines an input for a system module.  

Parameters
----------
* `input` :  
    A ComponentDefinition that defines the input  

Returns
-------
A FunctionalComponent that is derived from the argument ComponentDefinition and
configured as this ModuleDefinition's input (it's direction property is set to
SBOL_DIRECTION_IN)  
";

%feature("docstring") sbol::ModuleDefinition::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::ModuleDefinition::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::ModuleDefinition::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ModuleDefinition::setOutput "

Defines an output for a system module.  

Parameters
----------
* `output` :  
    A ComponentDefinition that defines the output  

Returns
-------
A FunctionalComponent that is derived from the argument ComponentDefinition and
configured as this ModuleDefinition's output (it's direction property is set to
SBOL_DIRECTION_OUT)  
";

%feature("docstring") sbol::ModuleDefinition::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ModuleDefinition::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ModuleDefinition::ModuleDefinition "

Construct a ModuleDefinition.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    valid Maven version string.  
";

%feature("docstring") sbol::ModuleDefinition::addToDocument "

Add the ModuleDefinition object to Document
";

// File: classsbol_1_1_owned_object.xml


%feature("docstring") sbol::OwnedObject "

A container property that contains child objects.  

Creates a composition out of two or more classes. In the SBOL specification,
compositional relationships are indicated in class diagrams by arrows with black
diamonds. A compositional relationship means that deleting the parent object
will delete the child objects, and adding the parent object to a Document will
also add the child object. Owned objects are stored in arbitrary order.  

templateparam
-------------
* `SBOLClass` :  
    The type of child SBOL object contained by this Property  
";

%feature("docstring") sbol::OwnedObject::validate "
";

%feature("docstring") sbol::OwnedObject::write "
";

%feature("docstring") sbol::OwnedObject::remove "

Remove an object from the list of objects and destroy it.  

Parameters
----------
* `uri` :  
    The identity of the object to be destroyed. This can be a displayId of the
    object or a full URI may be provided.  
* `index` :  
    A numerical index for the object. 
";

%feature("docstring") sbol::OwnedObject::get "

Get the child object.  

templateparam
-------------
* `SBOLClass` :  
    The type of the child object  
* `SBOLSubClass` :  
    A derived class of SBOLClass. Use this type specialization when adding
    multiple types of SBOLObjects to a container.  

Parameters
----------
* `uri` :  
    The specific URI for a child object if this OwnedObject property contains
    multiple objects,  

Returns
-------
A reference to the child object Returns a child object from the OwnedObject
property. If no URI is specified, the first object in this OwnedObject property
is returned.  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
";

%feature("docstring") sbol::OwnedObject::create "

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object contained in this OwnedObject property  
* `SBOLSubClass` :  
    A derived class of SBOLClass. Use this specialization for OwnedObject
    properties which contain multiple types of SBOLObjects.  

Parameters
----------
* `uri` :  
    If SBOLCompliance is enabled, this should be the displayId for the new child
    object. If not enabled, this should be a full raw URI.  

Returns
-------
A reference to the child object Autoconstructs a child object and attaches it to
the parent object. The new object will be constructed with default values
specified in the constructor for this type of object. If SBOLCompliance is
enabled, the child object's identity will be constructed using the supplied
displayId argument. Otherwise, the user should supply a full URI.  check
uniqueness of URI in Document  
";

%feature("docstring") sbol::OwnedObject::set "

Basic setter for OwnedObject SBOL IntProperty.

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object contained in this OwnedObject property  

Parameters
----------
* `sbol_obj` :  
    A child object to add to this container property. Assigns a child object to
    this OwnedObject container property. This method always overwrites the first
    SBOLObject in the container. appends another object to those already
    contained in this OwnedObject property. In SBOLCompliant mode, the create
    method is preferred  
* `sbol_obj` :  
    The child object Sets the first object in the container  
";

%feature("docstring") sbol::OwnedObject::clear "

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::OwnedObject::getAll "

Retrieve a vector of objects from the OwnedObject.

";

%feature("docstring") sbol::OwnedObject::getOwner "
";

%feature("docstring") sbol::OwnedObject::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::OwnedObject::getObjects "

Get all the objects contained in the property.  

Returns
-------
A vector of pointers to the objects  
";

%feature("docstring") sbol::OwnedObject::add "

Appends the new value to a list of values, for properties that allow it.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object contained in this OwnedObject property  
* `SBOLSubClass` :  
    A derived class of SBOLClass. Use this type specialization when adding
    multiple types of SBOLObjects to a container.  

Parameters
----------
* `sbol_obj` :  
    A child object to add to this container property. Adds a child object to the
    parent object. This method always appends another object to those already
    contained in this OwnedObject property. In SBOLCompliant mode, the create
    method is preferred  
";


// File: classsbol_1_1_participation.xml


%feature("docstring") sbol::Participation "

Each Participation represents how a particular FunctionalComponent behaves in
its parent Interaction.  
";

%feature("docstring") sbol::Participation::Participation "

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `participant` :  
    A reference to the participating FunctionalComponent in the parent
    Interaction  
";

%feature("docstring") sbol::Participation::Participation "
";

%feature("docstring") sbol::Participation::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Participation::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Participation::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Participation::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Participation::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Participation::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Participation::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Participation::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Participation::copy "
";

// File: classsbol_1_1_property.xml


%feature("docstring") sbol::Property "

Member properties of all SBOL objects are defined using a Property object.  

The Property class provides a generic interface for accessing SBOL objects. At a
low level, the Property class converts SBOL data structures into RDF triples.  

templateparam
-------------
* `The` :  
    SBOL specification currently supports string, URI, and integer literal
    values.  
";

%feature("docstring") sbol::Property::clear "

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::Property::getAll "

Retrieve a vector of objects from the Property.

";

%feature("docstring") sbol::Property::remove "

Remove a Property from the list of objects and destroy it.  

Parameters
----------
* `uri` :  
    The identity of the object to be destroyed. This can be a displayId of the
    object or a full URI may be provided.  
* `index` :  
    A numerical index for the object. 
";

%feature("docstring") sbol::Property::Property "

Parameters
----------
* `type_uri` :  
    An RDF hash URI for this property, consisting of a namespace followed by an
    identifier. For example, Properties of SBOLObjects use URIs of the form
    http://sbols.org/v2#somePropertyName, where the identifier somePropertyName
    determines the appearance of XML nodes in an SBOL file. Alternatively,
    annotations in a custom namespace can be provided using a similarly formed
    hash URI in another namespace.  
* `property_owner` :  
    All Property objects must have a pointer back to its parent SBOLObject of
    which it is a member  
* `initial_value` :  
    The initial value of the Property  
* `validation_rules` :  
    A vector of externally defined ValidationRules. The vector contains pointers
    to functions which correspond to the validation rules listed in the appendix
    of the formal SBOL specification document. ValidationRules are automatically
    checked every time a setter or adder method is called and when Documents are
    read and written.  
";

%feature("docstring") sbol::Property::write "
";

%feature("docstring") sbol::Property::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::Property::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Property::set "

Basic setter for SBOL Property.

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::Property::getOwner "
";

%feature("docstring") sbol::Property::validate "
";

// File: classsbol_1_1_range.xml


%feature("docstring") sbol::Range "

A Range object specifies a region via discrete, inclusive start and end
positions that correspond to indices for characters in the elements String of a
Sequence. Note that the index of the first location is 1, as is typical practice
in biology, rather than 0, as is typical practice in computer science.  
";

%feature("docstring") sbol::Range::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Range::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Range::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Range::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Range::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Range::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Range::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Range::Range "

Construct a Range.  

If operating in SBOL-compliant mode, use SequenceAnnotation.locations.create instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
* `start` :  
    An integer of 1 or greater  
* `end` :  
    An integer equal to or greater than the start  
";

%feature("docstring") sbol::Range::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Range::copy "
";

// File: classsbol_1_1_referenced_object.xml


%feature("docstring") sbol::ReferencedObject "

A reference to another SBOL object Contains a Uniform Resource Identifier (URI)
that refers to an an associated object.  

The object it points to may be another resource in this Document or an external
reference, for example to an object in an external repository. In the SBOL
specification, association by reference is indicated in class diagrams by arrows
with open (white) diamonds.  
";

%feature("docstring") sbol::ReferencedObject::create "

Creates another SBOL object derived from TopLevel and adds it to the Document.  

Parameters
----------
* `uri` :  
    In \"open world\" mode, this is a full URI and the same as the returned URI.
    If the default namespace for libSBOL has been configured, then this argument
    should simply be a local identifier. If SBOL-compliance is enabled, this
    argument should be the intended displayId of the new object. A full URI is
    automatically generated and returned.  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::ReferencedObject::validate "
";

%feature("docstring") sbol::ReferencedObject::write "
";

%feature("docstring") sbol::ReferencedObject::get "

Basic getter for all SBOL literal properties.  

Returns
-------
A string of characters used to identify a resource  
";

%feature("docstring") sbol::ReferencedObject::getOwner "
";

%feature("docstring") sbol::ReferencedObject::set "

Basic setter for SBOL ReferencedObject.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::ReferencedObject::remove "

Remove a ReferencedObject from the list of objects and destroy it.  

Parameters
----------
* `uri` :  
    The identity of the object to be destroyed. This can be a displayId of the
    object or a full URI may be provided.  
* `index` :  
    A numerical index for the object. 
";

%feature("docstring") sbol::ReferencedObject::addReference "
";

%feature("docstring") sbol::ReferencedObject::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::ReferencedObject::setReference "
";

%feature("docstring") sbol::ReferencedObject::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ReferencedObject::clear "

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
";

%feature("docstring") sbol::ReferencedObject::getAll "

Retrieve a vector of objects from the ReferencedObject.

";

// File: classsbol_1_1_s_b_o_l_error.xml


%feature("docstring") sbol::SBOLError "
";

%feature("docstring") sbol::SBOLError::what "
";

%feature("docstring") sbol::SBOLError::SBOLError "
";

// File: classsbol_1_1_s_b_o_l_object.xml


%feature("docstring") sbol::SBOLObject "

An SBOLObject converts a class data structure into an RDF triple store and
contains methods for serializing and parsing RDF triples.  
";

%feature("docstring") sbol::SBOLObject::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SBOLObject::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::SBOLObject::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SBOLObject::SBOLObject "
";

%feature("docstring") sbol::SBOLObject::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::SBOLObject::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SBOLObject::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SBOLObject::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SBOLObject::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

// File: classsbol_1_1_sequence.xml


%feature("docstring") sbol::Sequence "

The primary structure (eg, nucleotide or amino acid sequence) of a
ComponentDefinition object.  
";

%feature("docstring") sbol::Sequence::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Sequence::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::Sequence::Sequence "

Construct a ComponentDefinition.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `elements` :  
    A string representation of the primary structure of DNA, RNA, protein, or a
    SMILES string for small molecules.  
* `encoding` :  
    A URI that describes the representation format used for the elements
    property. Set to SBOL_ENCODING_IUPAC by default  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string.  
";

%feature("docstring") sbol::Sequence::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::Sequence::addToDocument "

Add the Sequence object to Document

";

%feature("docstring") sbol::Sequence::assemble "

Calculates the complete sequence of a high-level Component from the sequence of
its subcomponents.  

{rior to assembling the the complete sequence, you must assemble a template
design by calling ComponentDefinition::assemble for the ComponentDefinition that
references this Sequence.  

Parameters
----------
* `composite_sequence` :  
    Typically no value for the composite sequence should be specified by the
    user. This parameter is used to hold the composite sequence as it is passed
    to function calls at a higher-level of the recursion stack.  
";

%feature("docstring") sbol::Sequence::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Sequence::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Sequence::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::Sequence::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Sequence::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Sequence::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

// File: classsbol_1_1_sequence_annotation.xml


%feature("docstring") sbol::SequenceAnnotation "

The SequenceAnnotation class describes one or more regions of interest on the
Sequence objects referred to by its parent ComponentDefinition. In addition,
SequenceAnnotation objects can describe the substructure of their parent
ComponentDefinition through association with the Component objects contained by
this ComponentDefinition.  
";

%feature("docstring") sbol::SequenceAnnotation::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceAnnotation::SequenceAnnotation "

Construct a ComponentDefinition.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::SequenceAnnotation::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceAnnotation::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceAnnotation::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::SequenceAnnotation::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::SequenceAnnotation::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceAnnotation::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SequenceAnnotation::copy "
";

%feature("docstring") sbol::SequenceAnnotation::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

// File: classsbol_1_1_sequence_constraint.xml


%feature("docstring") sbol::SequenceConstraint "

The SequenceConstraint class can be used to assert restrictions on the relative,
sequence-based positions of pairs of Component objects contained by the same
parent ComponentDefinition. The primary purpose of this class is to enable the
specification of partially designed ComponentDefinition objects, for which the
precise positions or orientations of their contained Component objects are not
yet fully determined.  
";

%feature("docstring") sbol::SequenceConstraint::SequenceConstraint "

Construct a SequenceConstraint.  

If operating in SBOL-compliant mode, use
ComponentDefinition::sequenceConstraints::create instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
* `subject` :  
    Identity of the Component with this structural constraint  
* `object` :  
    Identity of the other Component with this structural constraint  
* `restriction` :  
    Flag indicating the type of structual constraint between the subject and
    object Components. By default, this is set to SBOL_RESTRICTION_PRECEDES  
";

%feature("docstring") sbol::SequenceConstraint::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceConstraint::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceConstraint::copy "
";

%feature("docstring") sbol::SequenceConstraint::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::SequenceConstraint::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SequenceConstraint::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

%feature("docstring") sbol::SequenceConstraint::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceConstraint::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SequenceConstraint::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_text_property.xml


%feature("docstring") sbol::TextProperty "

TextProperty objects are used to contain string literals.  

They can be used as member objects inside custom SBOL Extension classes.  
";

%feature("docstring") sbol::TextProperty::set "

Basic setter for SBOL TextProperty.

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::TextProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
A string literal  
";

%feature("docstring") sbol::TextProperty::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TextProperty::clear "

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::TextProperty::getAll "

Retrieve a vector of objects from the TextProperty.

";

%feature("docstring") sbol::TextProperty::getOwner "
";

%feature("docstring") sbol::TextProperty::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::TextProperty::remove "

Remove a TextProperty from the list of objects and destroy it.  

Parameters
----------
* `uri` :  
    The identity of the object to be destroyed. This can be a displayId of the
    object or a full URI may be provided.  
* `index` :  
    A numerical index for the object.
";

%feature("docstring") sbol::TextProperty::write "
";

%feature("docstring") sbol::TextProperty::validate "
";

%feature("docstring") sbol::TextProperty::TextProperty "
";

// File: classsbol_1_1_top_level.xml


%feature("docstring") sbol::TopLevel "

All SBOL classes derived from TopLevel appear as top level nodes in the RDF/XML
document tree and SBOL files. An abstract class.  
";

%feature("docstring") sbol::TopLevel::TopLevel "
";

%feature("docstring") sbol::TopLevel::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TopLevel::find "

Search this object recursively to see if an object with the URI already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::TopLevel::getClassName "

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TopLevel::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::TopLevel::addToDocument "

Add the TopLevel object to Document

";

%feature("docstring") sbol::TopLevel::compare "

Compare two SBOL objects or Documents.  

The behavior is currently undefined for objects with custom annotations or
extension classes.  

Parameters
----------
* `comparand` :  
    A pointer to the object being compared to this one.  

Returns
-------
1 if the objects are identical, 0 if they are different  
";

%feature("docstring") sbol::TopLevel::copy "

Copy an object and automatically increment its version.  

If the optional version argument is specified, it will be used instead of
incrementing the copied object's version. An object may also be copied into a
new document and a new namespace, assuming compliant URIs.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object being copied  

Parameters
----------
* `new_doc` :  
    The new copies will be attached to this Document. NULL by default.  
* `ns` :  
    This namespace will be substituted for the current namespace (as configured
    by setHomespace) in all SBOL-compliat URIs.  
* `version` :  
    A new version  

Returns
-------
The full URI of the created object.  
";

%feature("docstring") sbol::TopLevel::getPropertyValues "

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TopLevel::getPropertyValue "

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TopLevel::find_property "

Search this object recursively to see if it contains a member property with the
given RDF type.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  

Returns
-------
A pointer to the object that contains a member property with the specified RDF
type, NULL otherwise  
";

// File: classsbol_1_1_u_r_i_property.xml


%feature("docstring") sbol::URIProperty "

A URIProperty may contain a restricted type of string that conforms to the
specification for a Uniform Resource Identifier (URI), typically consisting of a
namespace authority followed by an identifier.  

A URIProperty often contains a reference to an SBOL object or may contain an
ontology term.  
";

%feature("docstring") sbol::URIProperty::write "
";

%feature("docstring") sbol::URIProperty::URIProperty "
";

%feature("docstring") sbol::URIProperty::getAll "

Retrieve a vector of objects from the URIProperty.

";

%feature("docstring") sbol::URIProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
A string of characters used to identify a resource  
";

%feature("docstring") sbol::URIProperty::set "

Basic setter for SBOL URIProperty.

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::URIProperty::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

// File: classsbol_1_1_version_property.xml


%feature("docstring") sbol::VersionProperty "

Contains a version number for an SBOL object.  

The VersionProperty follows Maven versioning semantics and includes a major,
minor, and patch version number. Specifically, libSBOL currently only supports
using '.' as a delimiter (e.g.: v2.0.1). If the user does not want to follow Maven
versioning, they can specify an arbitrary version string using the set() method.  
";

%feature("docstring") sbol::VersionProperty::getAll "

Retrieve a vector of objects from the VersionProperty.

";

%feature("docstring") sbol::VersionProperty::major "

Get major version.  

Returns
-------
The major version as an integer Splits the version string by a delimiter and
returns the major version number  
";

%feature("docstring") sbol::VersionProperty::set "

Basic setter for SBOL VersionProperty.

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::VersionProperty::getTypeURI "

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::VersionProperty::minor "

Get minor version.  

Returns
-------
The minor version as an integer Splits the version string by a delimiter and
returns the minor version number  
";

%feature("docstring") sbol::VersionProperty::VersionProperty "
";

%feature("docstring") sbol::VersionProperty::decrementMajor "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
A string literal  
";

%feature("docstring") sbol::VersionProperty::decrementMinor "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::remove "

Remove a VersionProperty from the list of objects and destroy it.  

Parameters
----------
* `uri` :  
    The identity of the object to be destroyed. This can be a displayId of the
    object or a full URI may be provided.  
* `index` :  
    A numerical index for the object.
";

%feature("docstring") sbol::VersionProperty::incrementMajor "

Increment major version.  
";

%feature("docstring") sbol::VersionProperty::incrementMinor "

Increment minor version.  
";

%feature("docstring") sbol::VersionProperty::validate "
";

%feature("docstring") sbol::VersionProperty::decrementPatch "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::incrementPatch "

Increment patch version.  
";

%feature("docstring") sbol::VersionProperty::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::VersionProperty::patch "

Get patch version.  

Returns
-------
The patch version as an integer Splits the version string by a delimiter and
returns the patch version  
";

%feature("docstring") sbol::VersionProperty::getOwner "
";

// File: namespacesbol.xml

%feature("docstring") sbol::toggleSBOLCompliantTypes "

Allows SBOL-compliant URIs.

Parameters
----------
* `is_toggled` : 
    Accepts boolean. The default value is false.  
";

%feature("docstring") sbol::hasHomespace "

Checks if a valid default namespace has been defined.  
";

%feature("docstring") sbol::compliantTypesEnabled "

Checks if an object's type is included in SBOL-compliant URIs.  
";

%feature("docstring") sbol::setHomespace "

Sets the default namespace for autocreation of URIs when a new SBOL object is
created.  

Parameters
----------
* `ns`:
    Homespace
";

%feature("docstring") sbol::create "
";

%feature("docstring") sbol::getFileFormat "

Returns currently accepted file format.  
";

%feature("docstring") sbol::exceptionsEnabled "

Checks if exception is enabled.  
";

%feature("docstring") sbol::toggleExceptions "

Function to toggle exception handling. 

Parameters
----------
* `is_toggled` : 
    Accepts boolean. The default value is false.  
";

%feature("docstring") sbol::setFileFormat "

Sets file format to use.  
";

%feature("docstring") sbol::getHomespace "

Returns the current default namespace for autocreation of URIs when a new SBOL
object is created.  
";

%feature("docstring") sbol::isSBOLCompliant "

Checks if SBOLCompliance is enabled.  
";

%feature("docstring") sbol::toggleSBOLCompliance "

Enables SBOLCompliance, which simplifies creation of URIs in constructor calls.

Parameters
----------
* `is_toggled` : 
    Accepts boolean. The default value is false.  
";


%feature("docstring") sbol::PartShop::count "
Return the count of objects contained in a PartShop
";

%feature("docstring") sbol::PartShop::pull "
Retrieve an object from an online resource

Parameters
----------
* `uri` : 
    The identity of the SBOL object you want to retrieve  
* `doc` :
	The Document to which SBOL data will be added
";        

%feature("docstring") sbol::PartShop::pullRootCollections "
Returns a Document containing all Collections in the PartShop that are not members of any other Collections. 
";    
        
%feature("docstring") sbol::PartShop::search "
An exact search. Scan the parts repository for objects that exactly match the specified criteria. In most uses of this function, LibSBOL's built-in RDF type constants (see @file constants.h) will come in handy. For instance, searching for all SBOL_COMPONENT_DEFINITION of type BIOPAX_DNA. (These constants follow a fairly systematic and consistent naming scheme (see @file constants.h). The number of records returned in the search is specified by offset and limit parameters. Metadata is return as a list of object metadata in dictionary format.

Parameters
----------
* `search_text` :
	This may be a literal text value or it may be a URI
* `object_type` :
	The RDF type of an SBOL object. For example, SBOL_COMPONENT_DEFINITION
* `property_uri` :
	The RDF type of an SBOL property. Specifies which field of an SBOL object to search. For example, SBOL_ROLES
* `offset` :
	The index of the first record to return. This parameter is indexed starting from zero
* `limit` :
	The total count number of records to return
";    

%feature("docstring") sbol::PartShop::search "
A general search. Search name, description, and displayId properties for a match to the search text, including matches to substrings of the property value. The type of object to search for can be further restricted by use of the second parameter, though this is set to SBOL_COMPONENT_DEFINITION by default. See @file constants.h for more of libSBOL's built-in RDF type constants. These constants follow a fairly predictable and consistent naming scheme. The number of records returned in the search is specified by offset and limit parameters. Metadata is return as a list of object metadata in dictionary format.

Parameters
----------
* `search_text` A snippet of text to search for in an SBOL object's displayId, name, and description fields
* `object_type` The RDF type of an SBOL object. For example, SBOL_COMPONENT_DEFINITION
* `offset` The index of the first record to return. This parameter is indexed starting from zero
* `limit` The total count number of records to return
";    
        
%feature("docstring") sbol::PartShop::search "
An advanced search that allows the user to specify an arbitrary number of search criteria as key/value pairs. Metadata is return as a list of object metadata in dictionary format.

Parameters
----------
* `q` :
	A SearchQuery object populated with search fields and values specified as key/value pairs
";
 
%feature("docstring") sbol::PartShop::submit "
Submit your SBOL data to a SynBioHub instance. In order to submit to a PartShop, you must login first. Register on [SynBioHub](http://synbiohub.org) to obtain account credentials.
* `doc` :
	The Document to submit
* `overwrite` :
	An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge
";

%feature("docstring") sbol::PartShop::login "
In order to submit to a PartShop, you must login first. Register on [SynBioHub](http://synbiohub.org) to obtain account credentials.

Parameters
----------
* `email` :
	The email associated with the user's SynBioHub account
* `password` :
	The user's password
";
        

// File: namespacestd.xml
