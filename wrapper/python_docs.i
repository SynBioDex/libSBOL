
// File: index.xml

// File: classsbol_1_1_component.xml
%feature("docstring") sbol::Component "

The Component class is used to compose ComponentDefinition objects
into a structural hierarchy. For example, the ComponentDefinition of a
gene could contain four Component objects: a promoter, RBS, CDS, and
terminator. In turn, the ComponentDefinition of the promoter Component
could contain Component objects defined as various operator sites.

C++ includes: component.h ";

%feature("docstring")  sbol::Component::Component "Component(std::string uri=DEFAULT_NS\"/Component/example\",
std::string definition=\"\", std::string access=SBOL_ACCESS_PUBLIC,
std::string version=\"1.0.0\") ";

%feature("docstring")  sbol::Component::~Component "virtual
~Component() ";

%feature("docstring")  sbol::Component::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Component::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Component::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Component::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Component::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Component::close "void close() ";


// File: classsbol_1_1_component_definition.xml
%feature("docstring") sbol::ComponentDefinition "

The ComponentDefinition class represents the structural entities of a
biological design.

The primary usage of this class is to represent structural entities
with designed sequences, such as DNA, RNA, and proteins, but it can
also be used to represent any other entity that is part of a design,
such as small molecules, proteins, and complexes

C++ includes: componentdefinition.h ";

%feature("docstring")  sbol::ComponentDefinition::ComponentDefinition
"ComponentDefinition(std::string
uri=DEFAULT_NS\"/ComponentDefinition/example\", std::string
type=BIOPAX_DNA, std::string version=\"1.0.0\")

Construct a ComponentDefinition.

Parameters:
-----------

uri:  A full URI including a scheme, namespace, and identifier. If
SBOLCompliance configuration is enabled, then this argument is simply
the displayId for the new object and a full URI will automatically be
constructed.

type:  A BioPAX ontology term that indicates whether the
ComponentDefinition is DNA, RNA, protein, or some other molecule type.

version:  An arbitrary version string. If SBOLCompliance is enabled,
this should be a Maven version string of the form
\"major.minor.patch\". ";

%feature("docstring")  sbol::ComponentDefinition::assemble "void
assemble(std::vector< ComponentDefinition * > list_of_components)

Assembles the provided vector of Components into a structural
hierarchy.

Autoconstructs the required Components and SequenceConstraints. The
resulting data structure is a partial design, still lacking a specific
DNA (or other) sequence. To fully realize a design, use
Sequence::assemble().

Parameters:
-----------

list_of_components:  A list of subcomponents that will compose this
ComponentDefinition ";

%feature("docstring")  sbol::ComponentDefinition::updateSequence "std::string updateSequence(std::string composite_sequence=\"\") ";

%feature("docstring")  sbol::ComponentDefinition::getInSequentialOrder
"std::vector<Component*> getInSequentialOrder()

Orders this ComponentDefinition's member Components into a linear
arrangement based on Sequence Constraints.

Primary sequence structure ";

%feature("docstring")  sbol::ComponentDefinition::hasUpstreamComponent
"int hasUpstreamComponent(Component &current_component)

Checks if the specified Component has a Component upstream in linear
arrangement on the DNA strand.

Checks that the appropriate SequenceConstraint exists.

Parameters:
-----------

current_component:  A Component in this ComponentDefinition

1 if found, 0 if not ";

%feature("docstring")  sbol::ComponentDefinition::getUpstreamComponent
"Component& getUpstreamComponent(Component &current_component)

Get the upstream Component.

The upstream component ";

%feature("docstring")
sbol::ComponentDefinition::hasDownstreamComponent "int
hasDownstreamComponent(Component &current_component)

Checks if the specified Component has a Component downstream in linear
arrangement on the DNA strand.

Checks that the appropriate SequenceConstraint exists.

Parameters:
-----------

current_component:  A Component in this ComponentDefinition

1 if found, 0 if not ";

%feature("docstring")
sbol::ComponentDefinition::getDownstreamComponent "Component&
getDownstreamComponent(Component &current_component)

Get the downstream Component.

The downstream component ";

%feature("docstring")  sbol::ComponentDefinition::getFirstComponent "Component& getFirstComponent()

Gets the first Component in a linear sequence.

The first component in sequential order ";

%feature("docstring")  sbol::ComponentDefinition::getLastComponent "Component& getLastComponent()

Gets the last Component in a linear sequence.

The last component in sequential order ";

%feature("docstring")  sbol::ComponentDefinition::participate "void
participate(Participation &species)

A convenience method that assigns a component to participate in a
biochemical reaction.

Behind the scenes, it auto-constructs a FunctionalComponent for this
ComponentDefinition and assigns it to a Participation

Parameters:
-----------

species:  A Participation object (ie, participant species in a
biochemical Interaction). ";

%feature("docstring")  sbol::ComponentDefinition::~ComponentDefinition
"virtual ~ComponentDefinition() ";

%feature("docstring")  sbol::ComponentDefinition::addToDocument "void
addToDocument(sbol::Document &) ";

%feature("docstring")  sbol::ComponentDefinition::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::ComponentDefinition::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::ComponentDefinition::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::ComponentDefinition::find "int
find(std::string uri) ";

%feature("docstring")  sbol::ComponentDefinition::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::ComponentDefinition::close "void close()
";


// File: classsbol_1_1_component_instance.xml
%feature("docstring") sbol::ComponentInstance "";

%feature("docstring")  sbol::ComponentInstance::~ComponentInstance "virtual ~ComponentInstance() ";

%feature("docstring")  sbol::ComponentInstance::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::ComponentInstance::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::ComponentInstance::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::ComponentInstance::find "int
find(std::string uri) ";

%feature("docstring")  sbol::ComponentInstance::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::ComponentInstance::close "void close()
";


// File: classsbol_1_1_config.xml
%feature("docstring") sbol::Config "

A class which contains global configuration variables for the libSBOL
environment. Intended to be used like a static class, configuration
variables are accessed through the `config' object.

C++ includes: config.h ";

%feature("docstring")  sbol::Config::Config "Config() ";

%feature("docstring")  sbol::Config::setHomespace "void
setHomespace(std::string ns) ";

%feature("docstring")  sbol::Config::getHomespace "std::string
getHomespace() ";

%feature("docstring")  sbol::Config::hasHomespace "int hasHomespace()
";

%feature("docstring")  sbol::Config::toggleSBOLCompliance "void
toggleSBOLCompliance() ";

%feature("docstring")  sbol::Config::isSBOLCompliant "int
isSBOLCompliant() ";

%feature("docstring")  sbol::Config::toggleExceptions "void
toggleExceptions() ";

%feature("docstring")  sbol::Config::exceptionsEnabled "int
exceptionsEnabled() ";


// File: classsbol_1_1_document.xml
%feature("docstring") sbol::Document "

Read and write SBOL using a Document class. The Document is a
container for Components, Modules, and all other SBOLObjects.

C++ includes: document.h ";

%feature("docstring")  sbol::Document::Document "Document()

Construct a Document. The Document is a container for Components,
Modules, and all other SBOLObjects. ";

%feature("docstring")  sbol::Document::getTopLevel "TopLevel&
getTopLevel(std::string) ";

%feature("docstring")  sbol::Document::getWorld "raptor_world*
getWorld() ";

%feature("docstring")  sbol::Document::add "void add(SBOLClass
&sbol_obj)

Register an object in the Document.

Parameters:
-----------

sbol_obj:  The SBOL object you want to serialize

Parameters:
-----------

SBOLClass:  The type of SBOL object ";

%feature("docstring")  sbol::Document::add "void add(std::vector<
SBOLClass * > sbol_objects)

Register an object in the Document.

Parameters:
-----------

sbol_objects:  A list of pointers to the SBOL objects you want to
serialize

Parameters:
-----------

SBOLClass:  The type of SBOL object ";

%feature("docstring")  sbol::Document::get "SBOLClass &
get(std::string uri)

Retrieve an object from the Document.

Parameters:
-----------

uri:  The identity of the SBOL object you want to retrieve

Parameters:
-----------

SBOLClass:  The type of SBOL object ";

%feature("docstring")  sbol::Document::getAll "std::vector<SBOLClass*> getAll()

Retrieve a vector of objects from the Document.

Parameters:
-----------

SBOLClass:  The type of SBOL objects ";

%feature("docstring")  sbol::Document::write "void write(std::string
filename)

Serialize all objects in this Document to an RDF/XML file.

Parameters:
-----------

filename:  The full name of the file you want to write (including file
extension) ";

%feature("docstring")  sbol::Document::read "void read(std::string
filename)

Read an RDF/XML file and attach the SBOL objects to this Document.

Existing contents of the Document will be wiped.

Parameters:
-----------

filename:  The full name of the file you want to read (including file
extension) ";

%feature("docstring")  sbol::Document::append "void
append(std::string filename)

Read an RDF/XML file and attach the SBOL objects to this Document.

New objects will be added to the existing contents of the Document

Parameters:
-----------

filename:  The full name of the file you want to read (including file
extension) ";

%feature("docstring")  sbol::Document::validate "void validate(void
*arg=NULL)

Run validation rules on this Document. Validation rules are called
automatically during parsing and serialization. ";

%feature("docstring")  sbol::Document::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Document::getNamespaces "std::vector<std::string> getNamespaces() ";

%feature("docstring")  sbol::Document::addNamespace "void
addNamespace(std::string ns, std::string prefix, raptor_serializer
*sbol_serializer) ";

%feature("docstring")  sbol::Document::addNamespace "void
addNamespace(std::string ns, std::string prefix) ";

%feature("docstring")  sbol::Document::flatten "std::vector<SBOLObject*> flatten() ";

%feature("docstring")  sbol::Document::close "void close(std::string
uri=\"\")

Delete all objects in this Document and destroy the Document. ";

%feature("docstring")  sbol::Document::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Document::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Document::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Document::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Document::close "void close() ";


// File: classsbol_1_1_functional_component.xml
%feature("docstring") sbol::FunctionalComponent "

The FunctionalComponent class is used to specify the functional usage
of a ComponentDefinition inside a ModuleDefinition. The
ModuleDefinition describes how the that describes how the
FunctionalComponent interacts with others and summarizes their
aggregate function.

C++ includes: component.h ";

%feature("docstring")  sbol::FunctionalComponent::FunctionalComponent
"FunctionalComponent(std::string
uri=DEFAULT_NS\"/FunctionalComponent/example\", std::string
definition=\"\", std::string access=SBOL_ACCESS_PUBLIC, std::string
direction=SBOL_DIRECTION_NONE, std::string version=\"1.0.0\")

Construct a FunctionalComponent.

Parameters:
-----------

A:  full URI including a scheme, namespace, and identifier. If
SBOLCompliance configuration is enabled, then this argument is simply
the displayId for the new object and a full URI will automatically be
constructed.

definition:

access:

direction:  The direction property specifies whether a
FunctionalComponent serves as an input, output, both, or neither for
its parent ModuleDefinition object

version:  An arbitrary version string. If SBOLCompliance is enabled,
this should be a Maven version string of the form
\"major.minor.patch\". ";

%feature("docstring")  sbol::FunctionalComponent::connect "void
connect(FunctionalComponent &interface_component)

This method connects module inputs and outputs.

Parameters:
-----------

interface_component:  An input or output component from another
ModuleDefinition that corresponds with this component. ";

%feature("docstring")  sbol::FunctionalComponent::mask "void
mask(FunctionalComponent &masked_component) ";

%feature("docstring")  sbol::FunctionalComponent::isMasked "int
isMasked() ";

%feature("docstring")  sbol::FunctionalComponent::~FunctionalComponent
"virtual ~FunctionalComponent() ";

%feature("docstring")  sbol::FunctionalComponent::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::FunctionalComponent::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::FunctionalComponent::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::FunctionalComponent::find "int
find(std::string uri) ";

%feature("docstring")  sbol::FunctionalComponent::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::FunctionalComponent::close "void close()
";


// File: classsbol_1_1_identified.xml
%feature("docstring") sbol::Identified "

All SBOL-defined classes are directly or indirectly derived from the
Identified abstract class.

An Identified object is identified using a Uniform Resource Identifier
(URI), a unique string that identifies and refers to a specific object
in an SBOL document or in an online resource such as a DNA repository.

C++ includes: identified.h ";

%feature("docstring")  sbol::Identified::~Identified "virtual
~Identified() ";

%feature("docstring")  sbol::Identified::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::Identified::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Identified::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Identified::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Identified::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Identified::close "void close() ";


// File: classsbol_1_1_interaction.xml
%feature("docstring") sbol::Interaction "

The Interaction class provides more detailed descriptionof how the
FunctionalComponents are intended to work together. For example, this
class can be used to represent different forms of genetic regulation
(e.g., transcriptional activation or repression), processes from the
central dogma of biology (e.g. transcription and translation), and
other basic molecular interactions (e.g., non-covalent binding or
enzymatic phosphorylation).

C++ includes: interaction.h ";

%feature("docstring")  sbol::Interaction::Interaction "Interaction(std::string uri=DEFAULT_NS\"/Interaction/example\",
std::string interaction_type=SBO_INTERACTION)

Construct an Interaction.

Parameters:
-----------

uri:  A full URI including a scheme, namespace, and identifier. If
SBOLCompliance configuration is enabled, then this argument is simply
the displayId for the new object and a full URI will automatically be
constructed.

interaction_type:  A Systems Biology Ontology term that describes a
biochemical interaction ";

%feature("docstring")  sbol::Interaction::~Interaction "virtual
~Interaction() ";

%feature("docstring")  sbol::Interaction::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::Interaction::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Interaction::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Interaction::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Interaction::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Interaction::close "void close() ";


// File: classsbol_1_1_int_property.xml
%feature("docstring") sbol::IntProperty "

IntProperty objects are used to contain integers.

They can be used as member objects inside custom SBOL Extension
classes.

C++ includes: properties.h ";

%feature("docstring")  sbol::IntProperty::IntProperty "IntProperty(sbol_type type_uri, void *property_owner, int
initial_value=0) ";

%feature("docstring")  sbol::IntProperty::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::IntProperty::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::IntProperty::get "virtual std::string
get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::IntProperty::set "virtual void
set(std::string new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::IntProperty::set "virtual void set(int
new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::IntProperty::add "void add(std::string
new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::IntProperty::write "virtual void write()
";

%feature("docstring")  sbol::IntProperty::validate "void
validate(void *arg=NULL) ";

%feature("docstring")  sbol::IntProperty::begin "iterator begin() ";

%feature("docstring")  sbol::IntProperty::end "iterator end() ";

%feature("docstring")  sbol::IntProperty::size "int size() ";


// File: classsbol_1_1_referenced_object_1_1iterator.xml
%feature("docstring") sbol::ReferencedObject::iterator "

Provides iterator functionality for SBOL properties that contain
multiple references.

C++ includes: object.h ";

%feature("docstring")  sbol::ReferencedObject::iterator::iterator "iterator(std::vector< std::string >::iterator i_str=std::vector<
std::string >::iterator()) ";


// File: classsbol_1_1_owned_object_1_1iterator.xml
%feature("docstring") sbol::OwnedObject::iterator "

Provides iterator functionality for SBOL properties that contain
multiple objects.

C++ includes: properties.h ";

%feature("docstring")  sbol::OwnedObject::iterator::iterator "iterator(typename std::vector< SBOLObject * >::iterator
i_object=std::vector< SBOLObject * >::iterator()) ";


// File: classsbol_1_1_property_1_1iterator.xml
%feature("docstring") sbol::Property::iterator "

Provides iterator functionality for SBOL properties that contain
multiple values.

C++ includes: property.h ";

%feature("docstring")  sbol::Property::iterator::iterator "iterator(typename std::vector< std::string >::iterator
i_str=std::vector< std::string >::iterator()) ";


// File: classsbol_1_1_list.xml
%feature("docstring") sbol::List "

Provides interface for an SBOL container Property that is allowed to
have more than one object or value.

Parameters:
-----------

PropertyType:  The type of SBOL Property, eg, Text, Int, OwnedObject,
etc

C++ includes: properties.h ";

%feature("docstring")  sbol::List::List "List(sbol_type type_uri,
SBOLObject *property_owner, std::string initial_value=\"\") ";

%feature("docstring")  sbol::List::remove "void remove(int index) ";


// File: classsbol_1_1_location.xml
%feature("docstring") sbol::Location "

The Location class specifies the strand orientation of a Component and
can be further extended by the Range, Cut, and GenericLocation
classes.

C++ includes: location.h ";

%feature("docstring")  sbol::Location::Location "Location(sbol_type
type=SBOL_LOCATION, std::string uri=DEFAULT_NS\"/Location/example\")
";

%feature("docstring")  sbol::Location::Location "Location(sbol_type,
std::string uri_prefix, std::string display_id, std::string version)
";

%feature("docstring")  sbol::Location::~Location "virtual ~Location()
";

%feature("docstring")  sbol::Location::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Location::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Location::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Location::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Location::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Location::close "void close() ";


// File: classsbol_1_1_maps_to.xml
%feature("docstring") sbol::MapsTo "

MapsTo objects provide a means to connect outputs and inputs of
ModuleDefinitions.

C++ includes: mapsto.h ";

%feature("docstring")  sbol::MapsTo::MapsTo "MapsTo(std::string
uri=DEFAULT_NS\"/MapsTo/example\", std::string local=\"\", std::string
remote=\"\", std::string refinement=SBOL_REFINEMENT_VERIFY_IDENTICAL)
";

%feature("docstring")  sbol::MapsTo::MapsTo "MapsTo(std::string
uri_prefix, std::string display_id, std::string version, std::string
local, std::string remote, std::string refinement) ";

%feature("docstring")  sbol::MapsTo::~MapsTo "virtual ~MapsTo() ";

%feature("docstring")  sbol::MapsTo::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::MapsTo::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::MapsTo::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::MapsTo::find "int find(std::string uri)
";

%feature("docstring")  sbol::MapsTo::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::MapsTo::close "void close() ";


// File: classsbol_1_1_model.xml
%feature("docstring") sbol::Model "

The purpose of the Model class is to serve as a placeholder for an
external computational model and provide additional meta-data to
enable better reasoning about the contents of this model.

In this way, there is minimal duplication of standardization efforts
and users of SBOL can formalize the function of a ModuleDefinition in
the language of their choice.

C++ includes: model.h ";

%feature("docstring")  sbol::Model::Model "Model(std::string
uri=DEFAULT_NS\"/Model/example\", std::string source=\"\", std::string
language=EDAM_SBML, std::string framework=SBO_CONTINUOUS, std::string
version=\"1.0.0\") ";

%feature("docstring")  sbol::Model::~Model "virtual ~Model() ";

%feature("docstring")  sbol::Model::addToDocument "void
addToDocument(sbol::Document &) ";

%feature("docstring")  sbol::Model::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Model::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Model::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Model::find "int find(std::string uri)
";

%feature("docstring")  sbol::Model::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Model::close "void close() ";


// File: classsbol_1_1_module.xml
%feature("docstring") sbol::Module "

The Module class represents a submodule of a ModuleDefinition within a
hierarchical design.

C++ includes: module.h ";

%feature("docstring")  sbol::Module::Module "Module(std::string
uri=DEFAULT_NS\"/Module/example\", std::string definition=\"\",
std::string version=\"1.0.0\") ";

%feature("docstring")  sbol::Module::~Module "virtual ~Module() ";

%feature("docstring")  sbol::Module::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Module::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Module::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Module::find "int find(std::string uri)
";

%feature("docstring")  sbol::Module::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Module::close "void close() ";


// File: classsbol_1_1_module_definition.xml
%feature("docstring") sbol::ModuleDefinition "

The ModuleDefinition class represents a grouping of structural and
functional entities in a biological design. The primary usage of this
class is to assert the molecular interactions and abstract function of
its child entities.

C++ includes: moduledefinition.h ";

%feature("docstring")  sbol::ModuleDefinition::ModuleDefinition "ModuleDefinition(std::string
uri=DEFAULT_NS\"/ModuleDefinition/example\", std::string
version=\"1.0.0\") ";

%feature("docstring")  sbol::ModuleDefinition::setOutput "FunctionalComponent& setOutput(ComponentDefinition &output) ";

%feature("docstring")  sbol::ModuleDefinition::setInput "FunctionalComponent& setInput(ComponentDefinition &input) ";

%feature("docstring")  sbol::ModuleDefinition::~ModuleDefinition "virtual ~ModuleDefinition() ";

%feature("docstring")  sbol::ModuleDefinition::assemble "void
assemble(std::vector< ModuleDefinition * > list_of_modules) ";

%feature("docstring")  sbol::ModuleDefinition::addToDocument "void
addToDocument(sbol::Document &) ";

%feature("docstring")  sbol::ModuleDefinition::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::ModuleDefinition::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::ModuleDefinition::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::ModuleDefinition::find "int
find(std::string uri) ";

%feature("docstring")  sbol::ModuleDefinition::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::ModuleDefinition::close "void close() ";


// File: classsbol_1_1_owned_object.xml
%feature("docstring") sbol::OwnedObject "

A container property that contains child objects.

Creates a composition out of two or more classes. In the SBOL
specification, compositional relationships are indicated in class
diagrams by arrows with black diamonds. A compositional relationship
means that deleting the parent object will delete the child objects,
and adding the parent object to a Document will also add the child
object. Owned objects are stored in arbitrary order.

Parameters:
-----------

SBOLClass:  The type of child SBOL object contained by this Property

C++ includes: properties.h ";

%feature("docstring")  sbol::OwnedObject::OwnedObject "OwnedObject(sbol_type type_uri=UNDEFINED, SBOLObject
*property_owner=NULL, std::string dummy=\"\") ";

%feature("docstring")  sbol::OwnedObject::OwnedObject "OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject
&first_object) ";

%feature("docstring")  sbol::OwnedObject::set "void set(SBOLClass
&sbol_obj)

Attach a child SBOL object to a parent SBOL object.

Parameters:
-----------

sbol_obj:  The child object Sets the first object in the container ";

%feature("docstring")  sbol::OwnedObject::get "SBOLClass & get(const
std::string object_id)

Get the child object.

Parameters:
-----------

object_id:  The URI of the child object

A reference to the child object ";

%feature("docstring")  sbol::OwnedObject::add "void add(SBOLClass
&sbol_obj)

Push another child object to the list, if the property allows multiple
values.

Parameters:
-----------

sbol_obj:  The child object ";

%feature("docstring")  sbol::OwnedObject::add "void add(SBOLSubClass
&sbol_obj) ";

%feature("docstring")  sbol::OwnedObject::get "SBOLSubClass & get()
";

%feature("docstring")  sbol::OwnedObject::copy "std::vector<
SBOLClass * > copy() ";

%feature("docstring")  sbol::OwnedObject::create "SBOLClass &
create(std::string uri)

Autoconstruct a child object and add it to a parent SBOL object.

Parameters:
-----------

If:  SBOLCompliance is enabled, this should be the displayId for the
new child object. If not enabled, this should be a full raw URI.

A reference to the child object Autoconstructs a child object and
attaches it to the parent object. If SBOLCompliance is enabled, the
child object's identity will be constructed using the supplied
displayId argument. Otherwise, the user should supply a full URI.
check uniqueness of URI in Document ";

%feature("docstring")  sbol::OwnedObject::create "void
create(std::string uri_prefix, std::string display_id, std::string
version)

Deprecate this ";

%feature("docstring")  sbol::OwnedObject::begin "iterator begin() ";

%feature("docstring")  sbol::OwnedObject::end "iterator end() ";

%feature("docstring")  sbol::OwnedObject::size "int size() ";

%feature("docstring")  sbol::OwnedObject::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::OwnedObject::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::OwnedObject::set "virtual void
set(std::string new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::OwnedObject::set "virtual void set(int
new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::OwnedObject::add "void add(std::string
new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::OwnedObject::write "virtual void write()
";

%feature("docstring")  sbol::OwnedObject::validate "void
validate(void *arg=NULL) ";


// File: classsbol_1_1_participation.xml
%feature("docstring") sbol::Participation "

Each Participation represents how a particular FunctionalComponent
behaves in its parent Interaction.

C++ includes: participation.h ";

%feature("docstring")  sbol::Participation::Participation "Participation(std::string uri=DEFAULT_NS\"/Participation/example\",
std::string participant=\"\", std::string version=\"1.0.0\")

Constructor.

Parameters:
-----------

uri:  A full URI including a scheme, namespace, and identifier. If
SBOLCompliance configuration is enabled, then this argument is simply
the displayId for the new object and a full URI will automatically be
constructed.

participant:  A reference to the participating FunctionalComponent in
the parent Interaction ";

%feature("docstring")  sbol::Participation::Participation "Participation(std::string uri, ComponentDefinition &species,
std::string version=\"1.0.0\") ";

%feature("docstring")  sbol::Participation::define "void
define(ComponentDefinition &species, std::string role=\"\") ";

%feature("docstring")  sbol::Participation::~Participation "virtual
~Participation() ";

%feature("docstring")  sbol::Participation::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::Participation::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Participation::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Participation::find "int
find(std::string uri) ";

%feature("docstring")  sbol::Participation::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Participation::close "void close() ";


// File: classsbol_1_1_property.xml
%feature("docstring") sbol::Property "

Member properties of all SBOL objects are defined using a Property
object.

The Property class provides a generic interface for accessing SBOL
objects. At a low level, the Property class converts SBOL data
structures into RDF triples.

Parameters:
-----------

The:  SBOL specification currently supports string, URI, and integer
literal values.

C++ includes: property.h ";

%feature("docstring")  sbol::Property::Property "Property(sbol_type
type_uri, void *property_owner, std::string initial_value,
ValidationRules validation_rules={})

Parameters:
-----------

type_uri:  An RDF hash URI for this property, consisting of a
namespace followed by an identifier. For example, Properties of
SBOLObjects use URIs of the formhttp://sbols.org/v2#somePropertyName,
where the identifier somePropertyName determines the appearance of XML
nodes in an SBOL file. Alternatively, annotations in a custom
namespace can be provided using a similarly formed hash URI in another
namespace.

property_owner:  All Property objects must have a pointer back to its
parent SBOLObject of which it is a member

initial_value:  The initial value of the Property

validation_rules:  A vector of externally defined ValidationRules. The
vector contains pointers to functions which correspond to the
validation rules listed in the appendix of the formal SBOL
specification document. ValidationRules are automatically checked
every time a setter or adder method is called and when Documents are
read and written. ";

%feature("docstring")  sbol::Property::Property "Property(sbol_type
type_uri, void *property_owner, int initial_value, ValidationRules
validation_rules={}) ";

%feature("docstring")  sbol::Property::Property "Property(sbol_type
type_uri=UNDEFINED, void *property_owner=NULL, ValidationRules
validation_rules={}) ";

%feature("docstring")  sbol::Property::~Property "~Property() ";

%feature("docstring")  sbol::Property::getTypeURI "sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Property::getOwner "SBOLObject &
getOwner() ";

%feature("docstring")  sbol::Property::get "std::string get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::Property::set "void set(std::string
new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::Property::set "void set(int new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::Property::add "void add(std::string
new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::Property::write "void write() ";

%feature("docstring")  sbol::Property::validate "void validate(void
*arg=NULL) ";

%feature("docstring")  sbol::Property::begin "iterator begin() ";

%feature("docstring")  sbol::Property::end "iterator end() ";

%feature("docstring")  sbol::Property::size "int size() ";


// File: classsbol_1_1_range.xml
%feature("docstring") sbol::Range "

A Range object specifies a region via discrete, inclusive start and
end positions that correspond to indices for characters in the
elements String of a Sequence. Note that the index of the first
location is 1, as is typical practice in biology, rather than 0, as is
typical practice in computer science.

C++ includes: location.h ";

%feature("docstring")  sbol::Range::Range "Range(std::string
uri=DEFAULT_NS\"/Range/example\", int start=1, int end=2) ";

%feature("docstring")  sbol::Range::Range "Range(std::string
uri_prefix, std::string display_id, std::string version, int start,
int end) ";

%feature("docstring")  sbol::Range::~Range "virtual ~Range() ";

%feature("docstring")  sbol::Range::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Range::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Range::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Range::find "int find(std::string uri)
";

%feature("docstring")  sbol::Range::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Range::close "void close() ";


// File: classsbol_1_1_referenced_object.xml
%feature("docstring") sbol::ReferencedObject "

A reference to another SBOL object Contains a Uniform Resource
Identifier (URI) that refers to an an associated object.

The object it points to may be another resource in this Document or an
external reference, for example to an object in an external
repository. In the SBOL specification, association by reference is
indicated in class diagrams by arrows with open (white) diamonds.

C++ includes: object.h ";

%feature("docstring")  sbol::ReferencedObject::ReferencedObject "ReferencedObject(sbol_type type_uri, sbol_type reference_type_uri,
SBOLObject *property_owner, std::string initial_value=\"\") ";

%feature("docstring")  sbol::ReferencedObject::ReferencedObject "ReferencedObject(sbol_type type_uri=UNDEFINED, SBOLObject
*property_owner=NULL, std::string initial_value=\"\") ";

%feature("docstring")  sbol::ReferencedObject::create "std::string
create(std::string uri) ";

%feature("docstring")  sbol::ReferencedObject::set "void
set(std::string uri) ";

%feature("docstring")  sbol::ReferencedObject::addReference "void
addReference(const std::string uri) ";

%feature("docstring")  sbol::ReferencedObject::setReference "void
setReference(const std::string uri) ";

%feature("docstring")  sbol::ReferencedObject::begin "iterator
begin() ";

%feature("docstring")  sbol::ReferencedObject::end "iterator end() ";

%feature("docstring")  sbol::ReferencedObject::size "int size() ";

%feature("docstring")  sbol::ReferencedObject::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::ReferencedObject::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::ReferencedObject::get "virtual
std::string get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::ReferencedObject::set "virtual void
set(int new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::ReferencedObject::add "void
add(std::string new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::ReferencedObject::write "virtual void
write() ";

%feature("docstring")  sbol::ReferencedObject::validate "void
validate(void *arg=NULL) ";


// File: classsbol_1_1_s_b_o_l_object.xml
%feature("docstring") sbol::SBOLObject "

An SBOLObject converts a C++ class data structure into an RDF triple
store and contains methods for serializing and parsing RDF triples.

C++ includes: object.h ";

%feature("docstring")  sbol::SBOLObject::SBOLObject "SBOLObject(std::string uri=DEFAULT_NS\"/SBOLObject/example\") ";

%feature("docstring")  sbol::SBOLObject::SBOLObject "SBOLObject(std::string uri_prefix, std::string display_id, std::string
version) ";

%feature("docstring")  sbol::SBOLObject::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::SBOLObject::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::SBOLObject::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::SBOLObject::find "int find(std::string
uri) ";

%feature("docstring")  sbol::SBOLObject::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::SBOLObject::~SBOLObject "virtual
~SBOLObject() ";

%feature("docstring")  sbol::SBOLObject::close "void close() ";


// File: classsbol_1_1_sequence.xml
%feature("docstring") sbol::Sequence "

The primary structure (eg, nucleotide or amino acid sequence) of a
ComponentDefinition object.

C++ includes: sequence.h ";

%feature("docstring")  sbol::Sequence::Sequence "Sequence(std::string
uri=DEFAULT_NS\"/Sequence/example\", std::string elements=\"\",
std::string encoding=SBOL_ENCODING_IUPAC, std::string
version=\"1.0.0\") ";

%feature("docstring")  sbol::Sequence::assemble "std::string
assemble(std::string composite_sequence=\"\") ";

%feature("docstring")  sbol::Sequence::~Sequence "virtual ~Sequence()
";

%feature("docstring")  sbol::Sequence::addToDocument "void
addToDocument(sbol::Document &) ";

%feature("docstring")  sbol::Sequence::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::Sequence::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::Sequence::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::Sequence::find "int find(std::string
uri) ";

%feature("docstring")  sbol::Sequence::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::Sequence::close "void close() ";


// File: classsbol_1_1_sequence_annotation.xml
%feature("docstring") sbol::SequenceAnnotation "

The SequenceAnnotation class describes one or more regions of interest
on the Sequence objects referred to by its parent ComponentDefinition.
In addition, SequenceAnnotation objects can describe the substructure
of their parent ComponentDefinition through association with the
Component objects contained by this ComponentDefinition.

C++ includes: sequenceannotation.h ";

%feature("docstring")  sbol::SequenceAnnotation::SequenceAnnotation "SequenceAnnotation(std::string
uri=DEFAULT_NS\"/SequenceAnnotation/example\", std::string
version=\"1.0.0\") ";

%feature("docstring")  sbol::SequenceAnnotation::~SequenceAnnotation "virtual ~SequenceAnnotation() ";

%feature("docstring")  sbol::SequenceAnnotation::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::SequenceAnnotation::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::SequenceAnnotation::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::SequenceAnnotation::find "int
find(std::string uri) ";

%feature("docstring")  sbol::SequenceAnnotation::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::SequenceAnnotation::close "void close()
";


// File: classsbol_1_1_sequence_constraint.xml
%feature("docstring") sbol::SequenceConstraint "

The SequenceConstraint class can be used to assert restrictions on the
relative, sequence- based positions of pairs of Component objects
contained by the same parent ComponentDefinition. The primary purpose
of this class is to enable the specification of partially designed
ComponentDefinition objects, for which the precise positions or
orientations of their contained Component objects are not yet fully
determined.

C++ includes: sequenceconstraint.h ";

%feature("docstring")  sbol::SequenceConstraint::SequenceConstraint "SequenceConstraint(std::string
uri=DEFAULT_NS\"/SequenceConstraint/example\", std::string
subject=\"\", std::string object=\"\", std::string
restriction=SBOL_RESTRICTION_PRECEDES, std::string version=\"1.0.0\")
";

%feature("docstring")  sbol::SequenceConstraint::~SequenceConstraint "virtual ~SequenceConstraint() ";

%feature("docstring")  sbol::SequenceConstraint::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::SequenceConstraint::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::SequenceConstraint::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::SequenceConstraint::find "int
find(std::string uri) ";

%feature("docstring")  sbol::SequenceConstraint::getClassName "std::string getClassName(std::string type) ";

%feature("docstring")  sbol::SequenceConstraint::close "void close()
";


// File: classsbol_1_1_text_property.xml
%feature("docstring") sbol::TextProperty "

TextProperty objects are used to contain string literals.

They can be used as member objects inside custom SBOL Extension
classes.

C++ includes: properties.h ";

%feature("docstring")  sbol::TextProperty::TextProperty "TextProperty(sbol_type type_uri, void *property_owner, std::string
initial_value=\"\") ";

%feature("docstring")  sbol::TextProperty::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::TextProperty::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::TextProperty::get "virtual std::string
get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::TextProperty::set "virtual void
set(std::string new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::TextProperty::set "virtual void set(int
new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::TextProperty::add "void add(std::string
new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::TextProperty::write "virtual void
write() ";

%feature("docstring")  sbol::TextProperty::validate "void
validate(void *arg=NULL) ";

%feature("docstring")  sbol::TextProperty::begin "iterator begin() ";

%feature("docstring")  sbol::TextProperty::end "iterator end() ";

%feature("docstring")  sbol::TextProperty::size "int size() ";


// File: classsbol_1_1_top_level.xml
%feature("docstring") sbol::TopLevel "

All SBOL classes derived from TopLevel appear as top level nodes in
the RDF/XML document tree and SBOL files. An abstract class.

C++ includes: toplevel.h ";

%feature("docstring")  sbol::TopLevel::addToDocument "void
addToDocument(sbol::Document &) ";

%feature("docstring")  sbol::TopLevel::~TopLevel "virtual ~TopLevel()
";

%feature("docstring")  sbol::TopLevel::getTypeURI "virtual sbol_type
getTypeURI() ";

%feature("docstring")  sbol::TopLevel::serialize "void
serialize(raptor_serializer *sbol_serializer, raptor_world
*sbol_world=NULL) ";

%feature("docstring")  sbol::TopLevel::nest "std::string
nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::TopLevel::find "int find(std::string
uri) ";

%feature("docstring")  sbol::TopLevel::getClassName "std::string
getClassName(std::string type) ";

%feature("docstring")  sbol::TopLevel::close "void close() ";


// File: classsbol_1_1_u_r_i_property.xml
%feature("docstring") sbol::URIProperty "

A URIProperty may contain a restricted type of string that conforms to
the specification for a Uniform Resource Identifier (URI), typically
consisting of a namespace authority followed by an identifier.

A URIProperty often contains a reference to an SBOL object or may
contain an ontology term.

C++ includes: properties.h ";

%feature("docstring")  sbol::URIProperty::URIProperty "URIProperty(sbol_type type_uri=UNDEFINED, void *property_owner=NULL,
std::string initial_value=\"\", ValidationRules validation_rules={})
";

%feature("docstring")  sbol::URIProperty::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::URIProperty::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::URIProperty::get "virtual std::string
get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::URIProperty::set "virtual void
set(std::string new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::URIProperty::set "virtual void set(int
new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::URIProperty::add "void add(std::string
new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::URIProperty::write "virtual void write()
";

%feature("docstring")  sbol::URIProperty::validate "void
validate(void *arg=NULL) ";

%feature("docstring")  sbol::URIProperty::begin "iterator begin() ";

%feature("docstring")  sbol::URIProperty::end "iterator end() ";

%feature("docstring")  sbol::URIProperty::size "int size() ";


// File: classsbol_1_1_version_property.xml
%feature("docstring") sbol::VersionProperty "

Contains a version number for an SBOL object.

The VersionProperty follows Maven versioning semantics and includes a
major, minor, and patch version number. Specifically, libSBOL
currently only supports using '.' as a delimiter. Ex: v2.0.1. If the
user does not want to follow Maven versioning, they can specify an
arbitrary version string using the set() method.

C++ includes: properties.h ";

%feature("docstring")  sbol::VersionProperty::incrementMajor "void
incrementMajor()

Increment major version. ";

%feature("docstring")  sbol::VersionProperty::incrementMinor "void
incrementMinor()

Increment minor version. ";

%feature("docstring")  sbol::VersionProperty::incrementPatch "void
incrementPatch()

Increment patch version. ";

%feature("docstring")  sbol::VersionProperty::decrementMinor "void
decrementMinor()

Decrement major version. ";

%feature("docstring")  sbol::VersionProperty::decrementMajor "void
decrementMajor()

Decrement major version. ";

%feature("docstring")  sbol::VersionProperty::decrementPatch "void
decrementPatch()

Decrement major version. ";

%feature("docstring")  sbol::VersionProperty::major "int major()

Get major version. ";

%feature("docstring")  sbol::VersionProperty::minor "int minor()

Get minor version. ";

%feature("docstring")  sbol::VersionProperty::patch "int patch()

Get patch version. ";

%feature("docstring")  sbol::VersionProperty::VersionProperty "VersionProperty(sbol_type type_uri, void *property_owner, std::string
initial_value=\"\") ";

%feature("docstring")  sbol::VersionProperty::getTypeURI "virtual
sbol_type getTypeURI() ";

%feature("docstring")  sbol::VersionProperty::getOwner "virtual
SBOLObject& getOwner() ";

%feature("docstring")  sbol::VersionProperty::get "virtual
std::string get()

Basic getter for all SBOL literal properties.

All properties are initially read from an SBOL file as a raw string
containing the property value. ";

%feature("docstring")  sbol::VersionProperty::set "virtual void
set(std::string new_value)

Basic setter for SBOL TextProperty and URIProperty.

Parameters:
-----------

new_value:  A new string value for the Property. ";

%feature("docstring")  sbol::VersionProperty::set "virtual void
set(int new_value)

Basic setter for SBOL IntProperty, but can be used with TextProperty
as well.

Parameters:
-----------

new_value:  A new integer value for the property, which is converted
to a raw string during serialization. ";

%feature("docstring")  sbol::VersionProperty::add "void
add(std::string new_value)

Appends the new value to a list of values, for properties that allow
it.

Parameters:
-----------

new_value:  A new string which will be added to a list of values. ";

%feature("docstring")  sbol::VersionProperty::write "virtual void
write() ";

%feature("docstring")  sbol::VersionProperty::validate "void
validate(void *arg=NULL) ";

%feature("docstring")  sbol::VersionProperty::begin "iterator begin()
";

%feature("docstring")  sbol::VersionProperty::end "iterator end() ";

%feature("docstring")  sbol::VersionProperty::size "int size() ";


// File: namespacesbol.xml
%feature("docstring")  sbol::setHomespace "void
sbol::setHomespace(std::string ns)

Set the default namespace for autocreation of URIs when a new SBOL
object is created. ";

%feature("docstring")  sbol::getHomespace "std::string
sbol::getHomespace()

Get the current default namespace for autocreation of URIs when a new
SBOL object is created. ";

%feature("docstring")  sbol::hasHomespace "int sbol::hasHomespace()

Checks if a valid default namespace has been defined. ";

%feature("docstring")  sbol::toggleSBOLCompliance "void
sbol::toggleSBOLCompliance()

Enables SBOLCompliance, which simplifies creation of URIs in
constructor calls. ";

%feature("docstring")  sbol::isSBOLCompliant "int
sbol::isSBOLCompliant()

Checks if SBOLCompliance is enabled. ";

%feature("docstring")  sbol::toggleExceptions "void
sbol::toggleExceptions() ";

%feature("docstring")  sbol::exceptionsEnabled "int
sbol::exceptionsEnabled() ";

%feature("docstring")  sbol::randomIdentifier "std::string
sbol::randomIdentifier() ";

%feature("docstring")  sbol::autoconstructURI "std::string
sbol::autoconstructURI() ";

%feature("docstring")  sbol::constructNonCompliantURI "std::string
sbol::constructNonCompliantURI(std::string uri) ";

%feature("docstring")  sbol::constructCompliantURI "std::string
sbol::constructCompliantURI(std::string sbol_type, std::string
display_id, std::string version) ";

%feature("docstring")  sbol::constructCompliantURI "std::string
sbol::constructCompliantURI(std::string parent_type, std::string
child_type, std::string display_id, std::string version) ";

%feature("docstring")  sbol::getCompliantURI "std::string
sbol::getCompliantURI(std::string uri_prefix, std::string
sbol_class_name, std::string display_id, std::string version) ";

%feature("docstring")  sbol::getClassName "std::string
sbol::getClassName(std::string type) ";

%feature("docstring")  sbol::getNameSpace "std::string
sbol::getNameSpace(std::string type) ";

%feature("docstring")  sbol::create "sbol::SBOLObject& sbol::create()
";

%feature("docstring")  sbol::register_extension "void
sbol::register_extension(std::string ns_prefix, std::string uri) ";

%feature("docstring")  sbol::raptor_error_handler "void
sbol::raptor_error_handler(void *user_data, raptor_log_message
*message) ";

%feature("docstring")  sbol::cut_sbol_resource "std::string
sbol::cut_sbol_resource(std::string &xml_string, const std::string
resource_id) ";

%feature("docstring")  sbol::replace_reference_to_resource "void
sbol::replace_reference_to_resource(std::string &xml_string, const
std::string property_name, const std::string resource_id, std::string
&replacement_text) ";

%feature("docstring")  sbol::seek_element "void
sbol::seek_element(std::istringstream &xml_buffer, std::string uri) ";

%feature("docstring")  sbol::seek_property_element "void
sbol::seek_property_element(std::istringstream &xml_buffer,
std::string property_name) ";

%feature("docstring")  sbol::seek_next_element "void
sbol::seek_next_element(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::seek_new_line "void
sbol::seek_new_line(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::seek_end_of_line "void
sbol::seek_end_of_line(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::seek_end_of_element "void
sbol::seek_end_of_element(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::seek_end_of_node "void
sbol::seek_end_of_node(std::istringstream &xml_buffer, std::string
uri) ";

%feature("docstring")  sbol::seek_resource "void
sbol::seek_resource(std::istringstream &xml_buffer, std::string
property_name, std::string uri) ";

%feature("docstring")  sbol::is_open_node "bool
sbol::is_open_node(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::indent "void sbol::indent(std::string
&text, int indentation) ";

%feature("docstring")  sbol::get_qname "std::string
sbol::get_qname(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::get_local_part "std::string
sbol::get_local_part(std::string qname) ";

%feature("docstring")  sbol::get_prefix "std::string
sbol::get_prefix(std::string qname) ";

%feature("docstring")  sbol::parse_element "std::vector<std::string>
sbol::parse_element(std::istringstream &xml_buffer) ";

%feature("docstring")  sbol::SBOLError "SBOLErrorCode
sbol::SBOLError(SBOLErrorCode error_code, const std::string message)
";

%feature("docstring")  sbol::sbolRule10101 "void
sbol::sbolRule10101(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::sbolRule10102 "void
sbol::sbolRule10102(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::sbol_rule_10202 "void
sbol::sbol_rule_10202(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::libsbol_rule_1 "void
sbol::libsbol_rule_1(void *sbol_obj, void *arg) ";


// File: _find_doxygen_8cmake.xml


// File: getting__started_8dox.xml


// File: installation_8dox.xml


// File: mainpage_8dox.xml


// File: modules_8dox.xml


// File: sequences_8dox.xml


// File: __dummy_8c.xml


// File: assembly_8h.xml


// File: source_2cmake__install_8cmake.xml


// File: manual_2cmake__install_8cmake.xml


// File: source_2_c_make_lists_8txt.xml
%feature("docstring")  include_directories "include_directories(${RAPTOR_INCLUDE_DIR}) FILE(GLOB SBOL_HEADER_FILES
const ants.h sbolerror.h config.h validation.h property.h properties.h
object.h identified.h toplevel.h sequenceannotation.h component.h
componentdefinition.h sequence.h document.h interaction.h
participation.h location.h sequenceconstraint.h moduledefinition.h
module.h mapsto.h model.h assembly.h sbol.h) FILE(GLOB
SBOL_SOURCE_FILES sbolerror.cpp config.cpp validation.cpp
properties.cpp object.cpp identified.cpp toplevel.cpp
componentdefinition.cpp document.cpp assembly.cpp)
get_directory_property(DirDefs COMPILE_DEFINITIONS) if($ ";

%feature("docstring")  if "MATCHES Windows if(SBOL_BUILD_32)
target_link_libraries(sbol $ ";


// File: manual_2_c_make_lists_8txt.xml
%feature("docstring")  CONFIGURE_FILE "CONFIGURE_FILE(${SBOL_MANUAL_DIR}/Doxyfile.in
${SBOL_MANUAL_DIR}/Doxyfile) ADD_CUSTOM_TARGET(sbol_manual ALL $ ";


// File: component_8h.xml


// File: componentdefinition_8h.xml


// File: config_8h.xml


// File: constants_8h.xml


// File: document_8h.xml


// File: generictoplevel_8h.xml


// File: host_8h.xml


// File: identified_8h.xml


// File: interaction_8h.xml


// File: location_8h.xml


// File: mapsto_8h.xml


// File: mergestaticlibs_8cmake.xml


// File: model_8h.xml


// File: module_8h.xml


// File: moduledefinition_8h.xml


// File: object_8h.xml


// File: participation_8h.xml


// File: properties_8h.xml


// File: property_8h.xml


// File: sbol_8h.xml


// File: sbol64__dummy_8c.xml


// File: sbolerror_8h.xml


// File: sbolobject_8h.xml


// File: sequence_8h.xml


// File: sequenceannotation_8h.xml


// File: sequenceannotationextension_8h.xml


// File: sequenceconstraint_8h.xml


// File: serializer_8c.xml
%feature("docstring")  hello_sbol "char* hello_sbol() ";


// File: serializer_8h.xml
%feature("docstring")  main "int main() ";


// File: toplevel_8h.xml


// File: validation_8h.xml


// File: group__sbol__core__data__model.xml


// File: group__extension__layer.xml


// File: getting_started.xml


// File: installation.xml


// File: modular_design.xml


// File: sequences.xml


// File: dir_b2f33c71d4aa5e7af42a1ca61ff5af1b.xml


// File: indexpage.xml

