
// File: index.xml

// File: classsbol_1_1_component.xml


%feature("docstring") sbol::Component "

The Component class is used to compose ComponentDefinition objects into a
structural hierarchy. For example, the ComponentDefinition of a gene could
contain four Component objects: a promoter, RBS, CDS, and terminator. In turn,
the ComponentDefinition of the promoter Component could contain Component
objects defined as various operator sites.  
";

%feature("docstring") sbol::Component::getClassName "
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

%feature("docstring") sbol::Component::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Component::copy "

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

%feature("docstring") sbol::Component::find "
";

%feature("docstring") sbol::Component::nest "
";

%feature("docstring") sbol::Component::serialize "
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

%feature("docstring") sbol::Component::isEqual "
";

%feature("docstring") sbol::Component::~Component "
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

%feature("docstring") sbol::ComponentDefinition::serialize "
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

%feature("docstring") sbol::ComponentDefinition::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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
";

%feature("docstring") sbol::ComponentDefinition::find "
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

%feature("docstring") sbol::ComponentDefinition::nest "
";

%feature("docstring") sbol::ComponentDefinition::~ComponentDefinition "
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

%feature("docstring") sbol::ComponentDefinition::addToDocument "
";

%feature("docstring") sbol::ComponentDefinition::getInSequentialOrder "

Orders this ComponentDefinition's member Components into a linear arrangement
based on Sequence Constraints.  

Returns
-------
Primary sequence structure  
";

%feature("docstring") sbol::ComponentDefinition::getClassName "
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

%feature("docstring") sbol::ComponentDefinition::isEqual "
";

%feature("docstring") sbol::ComponentDefinition::getTypeURI "
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
";

%feature("docstring") sbol::ComponentInstance::~ComponentInstance "
";

%feature("docstring") sbol::ComponentInstance::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::ComponentInstance::isEqual "
";

%feature("docstring") sbol::ComponentInstance::serialize "
";

%feature("docstring") sbol::ComponentInstance::nest "
";

%feature("docstring") sbol::ComponentInstance::find "
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
";

// File: classsbol_1_1_config.xml


%feature("docstring") sbol::Config "

A class which contains global configuration variables for the libSBOL
environment. Intended to be used like a static class, configuration variables
are accessed through the `config' object.  
";

%feature("docstring") sbol::Config::exceptionsEnabled "
";

%feature("docstring") sbol::Config::Config "
";

%feature("docstring") sbol::Config::setHomespace "
";

%feature("docstring") sbol::Config::setFileFormat "
";

%feature("docstring") sbol::Config::getHomespace "
";

%feature("docstring") sbol::Config::toggleExceptions "
";

%feature("docstring") sbol::Config::toggleSBOLCompliance "
";

%feature("docstring") sbol::Config::compliantTypesEnabled "
";

%feature("docstring") sbol::Config::hasHomespace "
";

%feature("docstring") sbol::Config::isSBOLCompliant "
";

%feature("docstring") sbol::Config::getFileFormat "
";

%feature("docstring") sbol::Config::toggleSBOLCompliantTypes "
";

// File: classsbol_1_1_cut.xml


%feature("docstring") sbol::Cut "

The Cut class specifies a location between two coordinates of a Sequence's
elements. class Cut : public Location.  
";

%feature("docstring") sbol::Cut::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Cut::~Cut "
";

%feature("docstring") sbol::Cut::serialize "
";

%feature("docstring") sbol::Cut::getTypeURI "
";

%feature("docstring") sbol::Cut::find "
";

%feature("docstring") sbol::Cut::copy "

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

%feature("docstring") sbol::Cut::nest "
";

%feature("docstring") sbol::Cut::isEqual "
";

%feature("docstring") sbol::Cut::getClassName "
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

If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create <
Cut > instead.  

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

%feature("docstring") sbol::Cut::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

// File: classsbol_1_1_document.xml


%feature("docstring") sbol::Document "

Read and write SBOL using a Document class. The Document is a container for
Components, Modules, and all other SBOLObjects.  
";

%feature("docstring") sbol::Document::addComponentDefinition "
Document.addComponentDefinition(componentDefinition)
Adds a component definition or a list of component definitions to a sbol::Document object.

Parameters
----------
* `componentDefinition` :  
    ComponentDefinition object or a list of ComponentDefinition objects
";

%feature("docstring") sbol::Document::addSequence "
Document.addSequence(sequence)
Adds a sequence or a list of sequences to a sbol::Document object.

Parameters
----------
* `sequence` :  
    Sequence object or a list of Sequence objects
";

%feature("docstring") sbol::Document::addModuleDefinition "
Document.addModuleDefinition(moduleDefinition)
Adds a module definition or a list of module definitions to a sbol::Document object.

Parameters
----------
* `moduleDefinition` :  
    ModuleDefinition object or a list of ModuleDefinition objects
";


%feature("docstring") sbol::Document::nest "
";

%feature("docstring") sbol::Document::getWorld "
";

%feature("docstring") sbol::Document::close "

Delete all objects in this Document and destroy the Document.  
";

%feature("docstring") sbol::Document::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Document::isEqual "
";

%feature("docstring") sbol::Document::Document "

Construct a Document. The Document is a container for Components, Modules, and
all other SBOLObjects.  
";

%feature("docstring") sbol::Document::add "

Register an object in the Document.  

Parameters
----------
* `sbol_obj` :  
    The SBOL object you want to serialize  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object  
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
";

%feature("docstring") sbol::Document::namespaceHandler "
";

%feature("docstring") sbol::Document::getClassName "
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
";

%feature("docstring") sbol::Document::addNamespace "
";

%feature("docstring") sbol::Document::parse_objects "
";

%feature("docstring") sbol::Document::getAll "

Retrieve a vector of objects from the Document.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL objects  
";

%feature("docstring") sbol::Document::find "
";

%feature("docstring") sbol::Document::getTypeURI "
";

%feature("docstring") sbol::Document::serialize "
";

%feature("docstring") sbol::Document::parse_properties "
";

%feature("docstring") sbol::Document::getNamespaces "
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

%feature("docstring") sbol::Document::flatten "
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

%feature("docstring") sbol::Document::getTopLevel "
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
";

%feature("docstring") sbol::FunctionalComponent::copy "

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

%feature("docstring") sbol::FunctionalComponent::serialize "
";

%feature("docstring") sbol::FunctionalComponent::nest "
";

%feature("docstring") sbol::FunctionalComponent::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
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

%feature("docstring") sbol::FunctionalComponent::isEqual "
";

%feature("docstring") sbol::FunctionalComponent::find "
";

%feature("docstring") sbol::FunctionalComponent::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::FunctionalComponent::~FunctionalComponent "
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
";

%feature("docstring") sbol::Identified::getTypeURI "
";

%feature("docstring") sbol::Identified::isEqual "
";

%feature("docstring") sbol::Identified::copy "

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

%feature("docstring") sbol::Identified::nest "
";

%feature("docstring") sbol::Identified::~Identified "
";

%feature("docstring") sbol::Identified::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Identified::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Identified::find "
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

%feature("docstring") sbol::Identified::serialize "
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

%feature("docstring") sbol::Interaction::find "
";

%feature("docstring") sbol::Interaction::getClassName "
";

%feature("docstring") sbol::Interaction::copy "

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

%feature("docstring") sbol::Interaction::nest "
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

%feature("docstring") sbol::Interaction::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Interaction::~Interaction "
";

%feature("docstring") sbol::Interaction::isEqual "
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

%feature("docstring") sbol::Interaction::serialize "
";

%feature("docstring") sbol::Interaction::getTypeURI "
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
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::IntProperty::size "
";

%feature("docstring") sbol::IntProperty::getOwner "
";

%feature("docstring") sbol::IntProperty::write "
";

%feature("docstring") sbol::IntProperty::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::IntProperty::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::IntProperty::getTypeURI "
";

%feature("docstring") sbol::IntProperty::validate "
";

%feature("docstring") sbol::IntProperty::begin "
";

%feature("docstring") sbol::IntProperty::end "
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

%feature("docstring") sbol::ReferencedObject::iterator::iterator "
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

%feature("docstring") sbol::List::remove "
";

%feature("docstring") sbol::List::remove "
";

%feature("docstring") sbol::List::List "
";

// File: classsbol_1_1_location.xml


%feature("docstring") sbol::Location "

The Location class specifies the strand orientation of a Component and can be
further extended by the Range, Cut, and GenericLocation classes.  
";

%feature("docstring") sbol::Location::copy "

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

%feature("docstring") sbol::Location::find "
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

%feature("docstring") sbol::Location::serialize "
";

%feature("docstring") sbol::Location::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Location::getClassName "
";

%feature("docstring") sbol::Location::~Location "
";

%feature("docstring") sbol::Location::Location "
";

%feature("docstring") sbol::Location::nest "
";

%feature("docstring") sbol::Location::isEqual "
";

%feature("docstring") sbol::Location::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
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

%feature("docstring") sbol::MapsTo::copy "

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

%feature("docstring") sbol::MapsTo::getClassName "
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

%feature("docstring") sbol::MapsTo::serialize "
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
";

%feature("docstring") sbol::MapsTo::nest "
";

%feature("docstring") sbol::MapsTo::~MapsTo "
";

%feature("docstring") sbol::MapsTo::isEqual "
";

%feature("docstring") sbol::MapsTo::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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
";

%feature("docstring") sbol::Model::serialize "
";

%feature("docstring") sbol::Model::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Model::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Model::isEqual "
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

%feature("docstring") sbol::Model::~Model "
";

%feature("docstring") sbol::Model::addToDocument "
";

%feature("docstring") sbol::Model::Model "
";

%feature("docstring") sbol::Model::getClassName "
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
";

%feature("docstring") sbol::Model::nest "
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

%feature("docstring") sbol::Module::~Module "
";

%feature("docstring") sbol::Module::find "
";

%feature("docstring") sbol::Module::nest "
";

%feature("docstring") sbol::Module::serialize "
";

%feature("docstring") sbol::Module::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Module::isEqual "
";

%feature("docstring") sbol::Module::getTypeURI "
";

%feature("docstring") sbol::Module::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Module::getClassName "
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

%feature("docstring") sbol::ModuleDefinition::serialize "
";

%feature("docstring") sbol::ModuleDefinition::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::ModuleDefinition::nest "
";

%feature("docstring") sbol::ModuleDefinition::assemble "
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

%feature("docstring") sbol::ModuleDefinition::setInput "
";

%feature("docstring") sbol::ModuleDefinition::isEqual "
";

%feature("docstring") sbol::ModuleDefinition::~ModuleDefinition "
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

%feature("docstring") sbol::ModuleDefinition::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ModuleDefinition::getClassName "
";

%feature("docstring") sbol::ModuleDefinition::setOutput "
";

%feature("docstring") sbol::ModuleDefinition::find "
";

%feature("docstring") sbol::ModuleDefinition::getTypeURI "
";

%feature("docstring") sbol::ModuleDefinition::ModuleDefinition "
";

%feature("docstring") sbol::ModuleDefinition::addToDocument "
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

%feature("docstring") sbol::OwnedObject::begin "
";

%feature("docstring") sbol::OwnedObject::get "

Get the child object.  

templateparam
-------------
* `SBOLClass` :  
    The type of the child object  

Parameters
----------
* `object_id` :  
    The URI of the child object  

Returns
-------
A reference to the child object  
";

%feature("docstring") sbol::OwnedObject::get "
";

%feature("docstring") sbol::OwnedObject::get "

Basic getter for all SBOL literal properties.  

Returns
-------
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
";

%feature("docstring") sbol::OwnedObject::create "

Autoconstruct a child object and add it to a parent SBOL object.  

templateparam
-------------
* `The` :  
    type of SBOL object that will be created  

Parameters
----------
* `If` :  
    SBOLCompliance is enabled, this should be the displayId for the new child
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

%feature("docstring") sbol::OwnedObject::create "
";

%feature("docstring") sbol::OwnedObject::create "

Deprecate this  
";

%feature("docstring") sbol::OwnedObject::set "

Attach a child SBOL object to a parent SBOL object.  

Parameters
----------
* `sbol_obj` :  
    The child object Sets the first object in the container  
";

%feature("docstring") sbol::OwnedObject::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::OwnedObject::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::OwnedObject::getTypeURI "
";

%feature("docstring") sbol::OwnedObject::copy "
";

%feature("docstring") sbol::OwnedObject::size "
";

%feature("docstring") sbol::OwnedObject::end "
";

%feature("docstring") sbol::OwnedObject::getOwner "
";

%feature("docstring") sbol::OwnedObject::add "

Push another child object to the list, if the property allows multiple values.  

Parameters
----------
* `sbol_obj` :  
    The child object  
";

%feature("docstring") sbol::OwnedObject::add "

Push an object of derived class to the list, eg, add a Range to a list of
Locations.  
";

%feature("docstring") sbol::OwnedObject::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

// File: classsbol_1_1_participation.xml


%feature("docstring") sbol::Participation "

Each Participation represents how a particular FunctionalComponent behaves in
its parent Interaction.  
";

%feature("docstring") sbol::Participation::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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

%feature("docstring") sbol::Participation::serialize "
";

%feature("docstring") sbol::Participation::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Participation::~Participation "
";

%feature("docstring") sbol::Participation::nest "
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
";

%feature("docstring") sbol::Participation::getClassName "
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
";

%feature("docstring") sbol::Participation::define "
";

%feature("docstring") sbol::Participation::isEqual "
";

%feature("docstring") sbol::Participation::copy "

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

%feature("docstring") sbol::Property::size "
";

%feature("docstring") sbol::Property::end "
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

%feature("docstring") sbol::Property::Property "
";

%feature("docstring") sbol::Property::Property "
";

%feature("docstring") sbol::Property::write "
";

%feature("docstring") sbol::Property::getOwner "
";

%feature("docstring") sbol::Property::~Property "
";

%feature("docstring") sbol::Property::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::Property::getTypeURI "
";

%feature("docstring") sbol::Property::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::Property::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::Property::begin "
";

%feature("docstring") sbol::Property::get "

Basic getter for all SBOL literal properties.  

Returns
-------
All properties are initially read from an SBOL file as a raw string containing
the property value.  
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
";

%feature("docstring") sbol::Range::serialize "
";

%feature("docstring") sbol::Range::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Range::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Range::isEqual "
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

%feature("docstring") sbol::Range::getClassName "
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

%feature("docstring") sbol::Range::~Range "
";

%feature("docstring") sbol::Range::getTypeURI "
";

%feature("docstring") sbol::Range::nest "
";

%feature("docstring") sbol::Range::Range "

Construct a Range.  

If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create <
Range > instead.  

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

%feature("docstring") sbol::Range::copy "

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

%feature("docstring") sbol::ReferencedObject::end "
";

%feature("docstring") sbol::ReferencedObject::write "
";

%feature("docstring") sbol::ReferencedObject::get "

Basic getter for all SBOL literal properties.  

Returns
-------
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::ReferencedObject::getOwner "
";

%feature("docstring") sbol::ReferencedObject::set "
";

%feature("docstring") sbol::ReferencedObject::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::ReferencedObject::begin "
";

%feature("docstring") sbol::ReferencedObject::validate "
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
";

%feature("docstring") sbol::ReferencedObject::size "
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
";

// File: classsbol_1_1_s_b_o_l_object.xml


%feature("docstring") sbol::SBOLObject "

An SBOLObject converts a C++ class data structure into an RDF triple store and
contains methods for serializing and parsing RDF triples.  
";

%feature("docstring") sbol::SBOLObject::nest "
";

%feature("docstring") sbol::SBOLObject::serialize "
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

%feature("docstring") sbol::SBOLObject::SBOLObject "
";

%feature("docstring") sbol::SBOLObject::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SBOLObject::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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

%feature("docstring") sbol::SBOLObject::find "
";

%feature("docstring") sbol::SBOLObject::~SBOLObject "
";

%feature("docstring") sbol::SBOLObject::getTypeURI "
";

%feature("docstring") sbol::SBOLObject::getClassName "
";

%feature("docstring") sbol::SBOLObject::isEqual "
";

// File: classsbol_1_1_sequence.xml


%feature("docstring") sbol::Sequence "

The primary structure (eg, nucleotide or amino acid sequence) of a
ComponentDefinition object.  
";

%feature("docstring") sbol::Sequence::find "
";

%feature("docstring") sbol::Sequence::Sequence "
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

%feature("docstring") sbol::Sequence::~Sequence "
";

%feature("docstring") sbol::Sequence::serialize "
";

%feature("docstring") sbol::Sequence::getClassName "
";

%feature("docstring") sbol::Sequence::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Sequence::addToDocument "
";

%feature("docstring") sbol::Sequence::assemble "
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
";

%feature("docstring") sbol::Sequence::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
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

%feature("docstring") sbol::Sequence::nest "
";

%feature("docstring") sbol::Sequence::isEqual "
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

%feature("docstring") sbol::SequenceAnnotation::~SequenceAnnotation "
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

%feature("docstring") sbol::SequenceAnnotation::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SequenceAnnotation::getClassName "
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

%feature("docstring") sbol::SequenceAnnotation::serialize "
";

%feature("docstring") sbol::SequenceAnnotation::getTypeURI "
";

%feature("docstring") sbol::SequenceAnnotation::find "
";

%feature("docstring") sbol::SequenceAnnotation::nest "
";

%feature("docstring") sbol::SequenceAnnotation::copy "

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

%feature("docstring") sbol::SequenceAnnotation::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SequenceAnnotation::isEqual "
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

%feature("docstring") sbol::SequenceConstraint::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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
";

%feature("docstring") sbol::SequenceConstraint::nest "
";

%feature("docstring") sbol::SequenceConstraint::copy "

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

%feature("docstring") sbol::SequenceConstraint::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SequenceConstraint::find "
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

%feature("docstring") sbol::SequenceConstraint::~SequenceConstraint "
";

%feature("docstring") sbol::SequenceConstraint::serialize "
";

%feature("docstring") sbol::SequenceConstraint::isEqual "
";

%feature("docstring") sbol::SequenceConstraint::getClassName "
";

// File: classsbol_1_1_text_property.xml


%feature("docstring") sbol::TextProperty "

TextProperty objects are used to contain string literals.  

They can be used as member objects inside custom SBOL Extension classes.  
";

%feature("docstring") sbol::TextProperty::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::TextProperty::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

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
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::TextProperty::getTypeURI "
";

%feature("docstring") sbol::TextProperty::validate "
";

%feature("docstring") sbol::TextProperty::size "
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

%feature("docstring") sbol::TextProperty::end "
";

%feature("docstring") sbol::TextProperty::write "
";

%feature("docstring") sbol::TextProperty::begin "
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
";

%feature("docstring") sbol::TopLevel::isEqual "
";

%feature("docstring") sbol::TopLevel::find "
";

%feature("docstring") sbol::TopLevel::close "

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
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

%feature("docstring") sbol::TopLevel::addToDocument "
";

%feature("docstring") sbol::TopLevel::~TopLevel "
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

%feature("docstring") sbol::TopLevel::nest "
";

%feature("docstring") sbol::TopLevel::getClassName "
";

%feature("docstring") sbol::TopLevel::getProperties "

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::TopLevel::serialize "
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

%feature("docstring") sbol::URIProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::URIProperty::size "
";

%feature("docstring") sbol::URIProperty::getTypeURI "
";

%feature("docstring") sbol::URIProperty::end "
";

%feature("docstring") sbol::URIProperty::validate "
";

%feature("docstring") sbol::URIProperty::begin "
";

%feature("docstring") sbol::URIProperty::getOwner "
";

%feature("docstring") sbol::URIProperty::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::URIProperty::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

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
using '.' as a delimiter. Ex: v2.0.1. If the user does not want to follow Maven
versioning, they can specify an arbitrary version string using the set() method.  
";

%feature("docstring") sbol::VersionProperty::incrementMinor "

Increment minor version.  
";

%feature("docstring") sbol::VersionProperty::validate "
";

%feature("docstring") sbol::VersionProperty::decrementMinor "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::decrementPatch "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::begin "
";

%feature("docstring") sbol::VersionProperty::getTypeURI "
";

%feature("docstring") sbol::VersionProperty::end "
";

%feature("docstring") sbol::VersionProperty::set "

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::VersionProperty::set "

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::VersionProperty::size "
";

%feature("docstring") sbol::VersionProperty::VersionProperty "
";

%feature("docstring") sbol::VersionProperty::split "
";

%feature("docstring") sbol::VersionProperty::add "

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::VersionProperty::decrementMajor "

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::incrementPatch "

Increment patch version.  
";

%feature("docstring") sbol::VersionProperty::major "

Get major version.  

Returns
-------
The major version as an integer Splits the version string by a delimiter and
returns the major version number  
";

%feature("docstring") sbol::VersionProperty::get "

Basic getter for all SBOL literal properties.  

Returns
-------
All properties are initially read from an SBOL file as a raw string containing
the property value.  
";

%feature("docstring") sbol::VersionProperty::write "
";

%feature("docstring") sbol::VersionProperty::minor "

Get minor version.  

Returns
-------
The minor version as an integer Splits the version string by a delimiter and
returns the minor version number  
";

%feature("docstring") sbol::VersionProperty::patch "

Get patch version.  

Returns
-------
The patch version as an integer Splits the version string by a delimiter and
returns the patch version  
";

%feature("docstring") sbol::VersionProperty::incrementMajor "

Increment major version.  
";

%feature("docstring") sbol::VersionProperty::getOwner "
";

// File: namespacesbol.xml

%feature("docstring") sbol::compliantTypesEnabled "

Checks if an object's type is included in SBOL-compliant URIs.  
";

%feature("docstring") sbol::cut_sbol_resource "
";

%feature("docstring") sbol::randomIdentifier "
";

%feature("docstring") sbol::seek_end_of_element "
";

%feature("docstring") sbol::create "
";

%feature("docstring") sbol::exceptionsEnabled "
";

%feature("docstring") sbol::seek_new_line "
";

%feature("docstring") sbol::get_local_part "
";

%feature("docstring") sbol::setFileFormat "
";

%feature("docstring") sbol::getHomespace "

Get the current default namespace for autocreation of URIs when a new SBOL
object is created.  
";

%feature("docstring") sbol::isSBOLCompliant "

Checks if SBOLCompliance is enabled.  
";

%feature("docstring") sbol::toggleSBOLCompliantTypes "

Turns option to include types in SBOL-compliant URIs on or off.  
";

%feature("docstring") sbol::hasHomespace "

Checks if a valid default namespace has been defined.  
";

%feature("docstring") sbol::is_open_node "
";

%feature("docstring") sbol::parseClassName "

Parse a class name from a URI.  

Parameters
----------
* `uri` :  
    A URI  
";

%feature("docstring") sbol::parse_element "
";

%feature("docstring") sbol::getFileFormat "
";

%feature("docstring") sbol::parseNamespace "
";

%feature("docstring") sbol::toggleExceptions "
";

%feature("docstring") sbol::seek_resource "
";

%feature("docstring") sbol::register_extension "

Deprecate this  
";

%feature("docstring") sbol::libsbol_rule_1 "
";

%feature("docstring") sbol::get_qname "
";

%feature("docstring") sbol::toggleSBOLCompliance "

Enables SBOLCompliance, which simplifies creation of URIs in constructor calls.  
";

%feature("docstring") sbol::parsePropertyName "
";

%feature("docstring") sbol::getCompliantURI "
";

%feature("docstring") sbol::seek_element "
";

%feature("docstring") sbol::setHomespace "

Set the default namespace for autocreation of URIs when a new SBOL object is
created.  
";

%feature("docstring") sbol::constructNonCompliantURI "
";

%feature("docstring") sbol::replace_reference_to_resource "
";

%feature("docstring") sbol::seek_end_of_node "
";

%feature("docstring") sbol::constructCompliantURI "
";

%feature("docstring") sbol::constructCompliantURI "
";

%feature("docstring") sbol::autoconstructURI "
";

%feature("docstring") sbol::indent "
";

%feature("docstring") sbol::seek_end_of_line "
";

%feature("docstring") sbol::get_prefix "
";

%feature("docstring") sbol::raptor_error_handler "
";

%feature("docstring") sbol::SBOLError "
";

%feature("docstring") sbol::seek_next_element "
";

%feature("docstring") sbol::seek_property_element "
";

// File: namespacestd.xml

// File: _biosystem_design_example_8cpp.xml

%feature("docstring") main "
";

// File: _c_r_i_s_p_r_repression_example_8cpp.xml

%feature("docstring") main "
";

// File: _sequence_assembly_example_8cpp.xml

%feature("docstring") main "
";

// File: _find_doxygen_8cmake.xml

// File: getting__started_8dox.xml

// File: installation_8dox.xml

// File: mainpage_8dox.xml

// File: modules_8dox.xml

// File: sequences_8dox.xml

// File: assembly_8cpp.xml

// File: assembly_8h.xml

// File: source_2cmake__install_8cmake.xml

// File: manual_2cmake__install_8cmake.xml

// File: source_2_c_make_lists_8txt.xml

%feature("docstring") include_directories "
";

%feature("docstring") if "
";

%feature("docstring") if "
";

// File: example_2_c_make_lists_8txt.xml

%feature("docstring") TARGET_LINK_LIBRARIES "
";

%feature("docstring") find_library "
";

%feature("docstring") find_library "
";

%feature("docstring") find_library "
";

%feature("docstring") SET "
";

%feature("docstring") SET "
";

%feature("docstring") cmake_policy "
";

// File: manual_2_c_make_lists_8txt.xml

%feature("docstring") CONFIGURE_FILE "
";

// File: component_8h.xml

// File: componentdefinition_8cpp.xml

// File: componentdefinition_8h.xml

// File: config_8cpp.xml

// File: config_8h.xml

// File: constants_8h.xml

// File: document_8cpp.xml

// File: document_8h.xml

// File: generictoplevel_8h.xml

// File: host_8h.xml

// File: identified_8cpp.xml

// File: identified_8h.xml

// File: igem__component_8h.xml

// File: interaction_8h.xml

// File: location_8h.xml

// File: mapsto_8h.xml

// File: mergestaticlibs_8cmake.xml

// File: model_8h.xml

// File: module_8h.xml

// File: moduledefinition_8h.xml

// File: object_8cpp.xml

// File: object_8h.xml

// File: participation_8h.xml

// File: properties_8cpp.xml

// File: properties_8h.xml

// File: property_8h.xml

// File: sbol_8cpp.xml

// File: sbol_8h.xml

// File: sbolerror_8cpp.xml

// File: sbolerror_8h.xml

// File: sbolobject_8cpp.xml

// File: sbolobject_8h.xml

// File: sequence_8h.xml

// File: sequenceannotation_8h.xml

// File: sequenceannotationextension_8h.xml

// File: sequenceconstraint_8h.xml

// File: serializer_8h.xml

%feature("docstring") main "
";

// File: toplevel_8cpp.xml

// File: toplevel_8h.xml

// File: validation_8cpp.xml

// File: validation_8h.xml

// File: group__sbol__core__data__model.xml

// File: group__extension__layer.xml

// File: getting_started.xml

// File: installation.xml

// File: modular_design.xml

// File: sequences.xml

// File: dir_cfafba98a580ce4b62f8a6fa96d7cbb0.xml

// File: dir_b2f33c71d4aa5e7af42a1ca61ff5af1b.xml

// File: indexpage.xml

