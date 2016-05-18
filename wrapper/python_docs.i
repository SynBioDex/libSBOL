
// Component

%feature("docstring") sbol::Component "
The Component class is used to compose ComponentDefinition objects into a structural hierarchy (ie, it is a subcomponent). For example, the ComponentDefinition of a gene could contain four Component objects: a promoter, RBS, CDS, and terminator. In turn, the ComponentDefinition of the promoter Component could contain Component objects defined as various operator sites.
";

%feature("docstring")  sbol::Component::Component(std::string uri, std::string definition, std::string access)
"
The basic constructor
@param uri Specifies the unique identity of this Component object
@param definition The identity (URI) of this Component's definition
";

%feature("docstring") sbol::Component::Component(std::string, std::string, std::string, std::string, std::string)
"
The compliant constructor.  The URI identity of the object is created from the first three arguments
@param uri_prefix The authority for the URI
@param display_id A name for the object that is more human-readable than the URI, but still machine-readable.  The display_id MUST be composed of only alphanumeric or underscore characters and MUST NOT begin with a 26 digit
";

%feature("docstring")  sbol::Component::~Component
"
The ComponentDefinition class represents the structural entities of a biological design. The primary usage of this class is to represent structural entities with designed sequences, such as DNA, RNA, and proteins, but it can also be used to represent any other entity that is part of a design, such as small molecules, molecular complexes, and light.
";

// ComponentDefinition
%feature("docstring") sbol::ComponentDefinition "";

%feature("docstring")  sbol::ComponentDefinition::ComponentDefinition
"sbol::ComponentDefinition::ComponentDefinition(std::string
uri=DEFAULT_NS\"/ComponentDefinition/example\", std::string
type=BIOPAX_DNA) ";

%feature("docstring")  sbol::ComponentDefinition::ComponentDefinition
"sbol::ComponentDefinition::ComponentDefinition(std::string
uri_prefix, std::string display_id, std::string version, std::string
type)
";

%feature("docstring")  sbol::ComponentDefinition::~ComponentDefinition
"";

%feature("docstring")  sbol::ComponentDefinition::types
"
@var List<TextProperty> The types property
";

%feature("docstring")  sbol::ComponentDefinition::roles
"
@var The roles property
";

%feature("docstring")  sbol::ComponentDefinition::sequences
"
The sequences property
";

// File: classsbol_1_1_component_instance.xml
%feature("docstring") sbol::ComponentInstance "";


// File: classsbol_1_1_document.xml
%feature("docstring") sbol::Document "

Read and write SBOL using a Document class. The Document is a
container for Components, Modules, and all other SBOLObjects.

C++ includes: document.h ";

%feature("docstring")  sbol::Document::Document "sbol::Document::Document() ";

%feature("docstring")  sbol::Document::getTopLevel "TopLevel&
sbol::Document::getTopLevel(std::string) ";

%feature("docstring")  sbol::Document::getWorld "raptor_world*
sbol::Document::getWorld() ";

%feature("docstring")  sbol::Document::add "void
sbol::Document::add(SBOLClass &sbol_obj) ";

%feature("docstring")  sbol::Document::get "SBOLClass &
sbol::Document::get(std::string uri) ";

%feature("docstring")  sbol::Document::write "void
sbol::Document::write(std::string filename) ";

%feature("docstring")  sbol::Document::read "void
sbol::Document::read(std::string filename) ";

%feature("docstring")  sbol::Document::validate "void
sbol::Document::validate(void *arg=NULL) ";

%feature("docstring")  sbol::Document::getNamespaces "std::vector<std::string> sbol::Document::getNamespaces() ";

%feature("docstring")  sbol::Document::flatten "std::vector<SBOLObject*> sbol::Document::flatten() ";

%feature("docstring")  sbol::Document::addNameSpace "void
sbol::Document::addNameSpace(std::string ns, std::string prefix,
raptor_serializer *sbol_serializer) ";


// File: classsbol_1_1_functional_component.xml
%feature("docstring") sbol::FunctionalComponent "";

%feature("docstring")  sbol::FunctionalComponent::FunctionalComponent
"sbol::FunctionalComponent::FunctionalComponent(std::string
uri=DEFAULT_NS\"/FunctionalComponent/example\", std::string
definition=\"\", std::string access=SBOL_ACCESS_PRIVATE, std::string
direction=SBOL_DIRECTION_NONE) ";

%feature("docstring")  sbol::FunctionalComponent::FunctionalComponent
"sbol::FunctionalComponent::FunctionalComponent(std::string
uri_prefix, std::string display_id, std::string version, std::string
definition, std::string access, std::string direction) ";

%feature("docstring")  sbol::FunctionalComponent::~FunctionalComponent
"sbol::FunctionalComponent::~FunctionalComponent() ";


// File: classsbol_1_1_generic_top_level.xml
%feature("docstring") sbol::GenericTopLevel "";

%feature("docstring")  sbol::GenericTopLevel::GenericTopLevel "sbol::GenericTopLevel::GenericTopLevel(std::string uri_prefix,
std::string display_id) ";


// File: classsbol_1_1_host.xml
%feature("docstring") sbol::Host "";

%feature("docstring")  sbol::Host::Host "sbol::Host::Host(std::string
uri=EXTENSION_NS\"example\") ";

%feature("docstring")  sbol::Host::~Host "sbol::Host::~Host() ";


// File: classsbol_1_1_identified.xml
%feature("docstring") sbol::Identified "";

%feature("docstring")  sbol::Identified::Identified "sbol::Identified::Identified(std::string
uri=DEFAULT_NS\"/Identified/example\") ";

%feature("docstring")  sbol::Identified::Identified "sbol::Identified::Identified(std::string prefix, std::string
display_id, std::string version) ";


// File: classsbol_1_1_interaction.xml
%feature("docstring") sbol::Interaction "";

%feature("docstring")  sbol::Interaction::Interaction "sbol::Interaction::Interaction(std::string
uri=DEFAULT_NS\"/Interaction/example\", std::string
interaction_type=SBO_INTERACTION) ";

%feature("docstring")  sbol::Interaction::Interaction "sbol::Interaction::Interaction(std::string uri_prefix, std::string
display_id, std::string version, std::string interaction_type) ";

%feature("docstring")  sbol::Interaction::~Interaction "sbol::Interaction::~Interaction() ";


// File: classsbol_1_1_int_property.xml
%feature("docstring") sbol::IntProperty "";

%feature("docstring")  sbol::IntProperty::IntProperty "sbol::IntProperty::IntProperty(sbol_type type_uri, void
*property_owner, int initial_value=0) ";


// File: classsbol_1_1_owned_object_1_1iterator.xml
%feature("docstring") sbol::OwnedObject::iterator "";

%feature("docstring")  sbol::OwnedObject::iterator::iterator "sbol::OwnedObject< SBOLClass >::iterator::iterator(typename
std::vector< SBOLObject * >::iterator i_object=std::vector< SBOLObject
* >::iterator()) ";


// File: classsbol_1_1_referenced_object_1_1iterator.xml
%feature("docstring") sbol::ReferencedObject::iterator "";

%feature("docstring")  sbol::ReferencedObject::iterator::iterator "sbol::ReferencedObject< SBOLClass >::iterator::iterator(typename
std::vector< std::string >::iterator i_str=std::vector< std::string
>::iterator()) ";


// File: classsbol_1_1_property_1_1iterator.xml
%feature("docstring") sbol::Property::iterator "";

%feature("docstring")  sbol::Property::iterator::iterator "sbol::Property< LiteralType >::iterator::iterator(typename
std::vector< std::string >::iterator i_str=std::vector< std::string
>::iterator()) ";


// File: classsbol_1_1_list.xml
%feature("docstring") sbol::List "";

%feature("docstring")  sbol::List::List "sbol::List< PropertyType
>::List(sbol_type type_uri, SBOLObject *property_owner, std::string
initial_value=\"\") ";

%feature("docstring")  sbol::List::remove "void sbol::List<
PropertyType >::remove(int index) ";


// File: classsbol_1_1_location.xml
%feature("docstring") sbol::Location "";

%feature("docstring")  sbol::Location::Location "sbol::Location::Location(sbol_type type=SBOL_LOCATION, std::string
uri=DEFAULT_NS\"/Location/example\") ";

%feature("docstring")  sbol::Location::Location "sbol::Location::Location(sbol_type, std::string uri_prefix,
std::string display_id, std::string version) ";


// File: classsbol_1_1_maps_to.xml
%feature("docstring") sbol::MapsTo "";

%feature("docstring")  sbol::MapsTo::MapsTo "sbol::MapsTo::MapsTo(std::string uri=DEFAULT_NS\"/MapsTo/example\",
std::string local=\"\", std::string remote=\"\", std::string
refinement=SBOL_REFINEMENT_VERIFY_IDENTICAL) ";

%feature("docstring")  sbol::MapsTo::MapsTo "sbol::MapsTo::MapsTo(std::string uri_prefix, std::string display_id,
std::string version, std::string local, std::string remote,
std::string refinement) ";

%feature("docstring")  sbol::MapsTo::~MapsTo "sbol::MapsTo::~MapsTo()
";


// File: classsbol_1_1_model.xml
%feature("docstring") sbol::Model "";

%feature("docstring")  sbol::Model::Model "sbol::Model::Model(std::string uri=DEFAULT_NS\"/Model/example\",
std::string source=\"\", std::string language=EDAM_SBML, std::string
framework=SBO_CONTINUOUS) ";

%feature("docstring")  sbol::Model::Model "sbol::Model::Model(std::string uri_prefix, std::string display_id,
std::string version, std::string source, std::string language,
std::string framework) ";

%feature("docstring")  sbol::Model::~Model "sbol::Model::~Model() ";


// File: classsbol_1_1_module.xml
%feature("docstring") sbol::Module "";

%feature("docstring")  sbol::Module::Module "sbol::Module::Module(std::string uri=DEFAULT_NS\"/Module/example\",
std::string definition=\"\") ";

%feature("docstring")  sbol::Module::Module "sbol::Module::Module(std::string uri_prefix, std::string display_id,
std::string version, std::string definition) ";

%feature("docstring")  sbol::Module::~Module "sbol::Module::~Module()
";


// File: classsbol_1_1_module_definition.xml
%feature("docstring") sbol::ModuleDefinition "";

%feature("docstring")  sbol::ModuleDefinition::ModuleDefinition "sbol::ModuleDefinition::ModuleDefinition(std::string
uri=DEFAULT_NS\"/ModuleDefinition/example\") ";

%feature("docstring")  sbol::ModuleDefinition::ModuleDefinition "sbol::ModuleDefinition::ModuleDefinition(std::string uri_prefix,
std::string display_id, std::string version) ";

%feature("docstring")  sbol::ModuleDefinition::~ModuleDefinition "sbol::ModuleDefinition::~ModuleDefinition() ";


// File: classsbol_1_1_owned_object.xml
%feature("docstring") sbol::OwnedObject "";

%feature("docstring")  sbol::OwnedObject::OwnedObject "sbol::OwnedObject< SBOLClass >::OwnedObject(sbol_type
type_uri=UNDEFINED, SBOLObject *property_owner=NULL, std::string
dummy=\"\") ";

%feature("docstring")  sbol::OwnedObject::OwnedObject "sbol::OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, void
*property_owner, SBOLObject &first_object) ";

%feature("docstring")  sbol::OwnedObject::add "void
sbol::OwnedObject< SBOLClass >::add(SBOLClass &sbol_obj) ";

%feature("docstring")  sbol::OwnedObject::set "void
sbol::OwnedObject< SBOLClass >::set(SBOLClass &sbol_obj) ";

%feature("docstring")  sbol::OwnedObject::get "SBOLClass &
sbol::OwnedObject< SBOLClass >::get(const std::string object_id) ";

%feature("docstring")  sbol::OwnedObject::copy "std::vector<
SBOLClass * > sbol::OwnedObject< SBOLClass >::copy() ";

%feature("docstring")  sbol::OwnedObject::create "void
sbol::OwnedObject< SBOLClass >::create(std::string uri) ";

%feature("docstring")  sbol::OwnedObject::create "void
sbol::OwnedObject< SBOLClass >::create(std::string uri_prefix,
std::string display_id, std::string version) ";

%feature("docstring")  sbol::OwnedObject::begin "iterator
sbol::OwnedObject< SBOLClass >::begin() ";

%feature("docstring")  sbol::OwnedObject::end "iterator
sbol::OwnedObject< SBOLClass >::end() ";


// File: classsbol_1_1_participation.xml
%feature("docstring") sbol::Participation "";

%feature("docstring")  sbol::Participation::Participation "sbol::Participation::Participation(std::string
uri=DEFAULT_NS\"/Participation/example\", std::string
participant=\"\") ";

%feature("docstring")  sbol::Participation::Participation "sbol::Participation::Participation(std::string uri_prefix, std::string
display_id, std::string version, std::string participant) ";

%feature("docstring")  sbol::Participation::~Participation "sbol::Participation::~Participation() ";


// File: classsbol_1_1_property.xml
%feature("docstring") sbol::Property "

metafunction for generation of a map of message types to their
associated callbacks.

Usage: Use generate_callback_map<Type>::type to ...

Parameters:
-----------

LiteralType:  The library currently supports Property<string> and
Property<int> specification currently supports integer, string, and
URI literals

C++ includes: property.h ";

%feature("docstring")  sbol::Property::Property "sbol::Property<
LiteralType >::Property(sbol_type type_uri, void *property_owner,
std::string initial_value, ValidationRules validation_rules={}) ";

%feature("docstring")  sbol::Property::Property "sbol::Property<
LiteralType >::Property(sbol_type type_uri, void *property_owner, int
initial_value, ValidationRules validation_rules={}) ";

%feature("docstring")  sbol::Property::Property "sbol::Property<
LiteralType >::Property(sbol_type type_uri=UNDEFINED, void
*property_owner=NULL, ValidationRules validation_rules={}) ";

%feature("docstring")  sbol::Property::~Property "sbol::Property<
LiteralType >::~Property() ";

%feature("docstring")  sbol::Property::getTypeURI "sbol_type
sbol::Property< LiteralType >::getTypeURI() ";

%feature("docstring")  sbol::Property::getOwner "SBOLObject &
sbol::Property< LiteralType >::getOwner() ";

%feature("docstring")  sbol::Property::get "std::string
sbol::Property< LiteralType >::get() ";

%feature("docstring")  sbol::Property::add "void sbol::Property<
LiteralType >::add(std::string new_value) ";

%feature("docstring")  sbol::Property::set "void sbol::Property<
LiteralType >::set(std::string new_value) ";

%feature("docstring")  sbol::Property::set "void sbol::Property<
LiteralType >::set(int new_value) ";

%feature("docstring")  sbol::Property::write "void sbol::Property<
LiteralType >::write() ";

%feature("docstring")  sbol::Property::validate "void sbol::Property<
LiteralType >::validate(void *arg=NULL) ";

%feature("docstring")  sbol::Property::begin "iterator
sbol::Property< LiteralType >::begin() ";

%feature("docstring")  sbol::Property::end "iterator sbol::Property<
LiteralType >::end() ";


// File: classsbol_1_1_range.xml
%feature("docstring") sbol::Range "";

%feature("docstring")  sbol::Range::Range "sbol::Range::Range(std::string uri=DEFAULT_NS\"/Range/example\", int
start=1, int end=2) ";

%feature("docstring")  sbol::Range::Range "sbol::Range::Range(std::string uri_prefix, std::string display_id,
std::string version, int start, int end) ";

%feature("docstring")  sbol::Range::~Range "sbol::Range::~Range() ";


// File: classsbol_1_1_referenced_object.xml
%feature("docstring") sbol::ReferencedObject "";

%feature("docstring")  sbol::ReferencedObject::ReferencedObject "sbol::ReferencedObject< SBOLClass >::ReferencedObject(sbol_type
type_uri=UNDEFINED, SBOLObject *property_owner=NULL, std::string
dummy=\"\") ";

%feature("docstring")  sbol::ReferencedObject::ReferencedObject "sbol::ReferencedObject< SBOLClass >::ReferencedObject(sbol_type
type_uri, sbol_type reference_type_uri, SBOLObject *property_owner,
std::string initial_value=\"\") ";

%feature("docstring")  sbol::ReferencedObject::ReferencedObject "sbol::ReferencedObject< SBOLClass >::ReferencedObject(sbol_type
type_uri, void *property_owner, SBOLObject &first_object) ";

%feature("docstring")  sbol::ReferencedObject::add "void
sbol::ReferencedObject< SBOLClass >::add(SBOLClass &sbol_obj) ";

%feature("docstring")  sbol::ReferencedObject::set "void
sbol::ReferencedObject< SBOLClass >::set(std::string uri) ";

%feature("docstring")  sbol::ReferencedObject::set "void
sbol::ReferencedObject< SBOLClass >::set(SBOLClass &sbol_obj) ";

%feature("docstring")  sbol::ReferencedObject::get "SBOLClass &
sbol::ReferencedObject< SBOLClass >::get(std::string object_id) ";

%feature("docstring")  sbol::ReferencedObject::addReference "void
sbol::ReferencedObject< SBOLClass >::addReference(const std::string
uri) ";

%feature("docstring")  sbol::ReferencedObject::addReference "void
sbol::ReferencedObject< SBOLClass >::addReference(const std::string
uri_prefix, const std::string display_id) ";

%feature("docstring")  sbol::ReferencedObject::addReference "void
sbol::ReferencedObject< SBOLClass >::addReference(const std::string
uri_prefix, const std::string display_id, const std::string version)
";

%feature("docstring")  sbol::ReferencedObject::setReference "void
sbol::ReferencedObject< SBOLClass >::setReference(const std::string
uri) ";

%feature("docstring")  sbol::ReferencedObject::setReference "void
sbol::ReferencedObject< SBOLClass >::setReference(const std::string
uri_prefix, const std::string display_id) ";

%feature("docstring")  sbol::ReferencedObject::setReference "void
sbol::ReferencedObject< SBOLClass >::setReference(const std::string
uri_prefix, const std::string display_id, const std::string version)
";

%feature("docstring")  sbol::ReferencedObject::begin "iterator
sbol::ReferencedObject< SBOLClass >::begin() ";

%feature("docstring")  sbol::ReferencedObject::end "iterator
sbol::ReferencedObject< SBOLClass >::end() ";


// File: classsbol_1_1_s_b_o_l_object.xml
%feature("docstring") sbol::SBOLObject "";

%feature("docstring")  sbol::SBOLObject::SBOLObject "sbol::SBOLObject::SBOLObject(std::string
uri=DEFAULT_NS\"/SBOLObject/example\") ";

%feature("docstring")  sbol::SBOLObject::SBOLObject "sbol::SBOLObject::SBOLObject(std::string uri_prefix, std::string
display_id, std::string version) ";

%feature("docstring")  sbol::SBOLObject::~SBOLObject "sbol::SBOLObject::~SBOLObject() ";

%feature("docstring")  sbol::SBOLObject::getTypeURI "virtual
sbol_type sbol::SBOLObject::getTypeURI() ";

%feature("docstring")  sbol::SBOLObject::serialize "void
sbol::SBOLObject::serialize(raptor_serializer *sbol_serializer,
raptor_world *sbol_world=NULL) ";

%feature("docstring")  sbol::SBOLObject::nest "std::string
sbol::SBOLObject::nest(std::string &rdfxml_buffer) ";

%feature("docstring")  sbol::SBOLObject::getClassName "std::string
sbol::SBOLObject::getClassName(std::string type) ";


// File: classsbol_1_1_sequence.xml
%feature("docstring") sbol::Sequence "";

%feature("docstring")  sbol::Sequence::Sequence "sbol::Sequence::Sequence(std::string
uri=DEFAULT_NS\"/Sequence/example\", std::string elements=\"\",
std::string encoding=SBOL_ENCODING_IUPAC) ";

%feature("docstring")  sbol::Sequence::Sequence "sbol::Sequence::Sequence(std::string uri_prefix, std::string
display_id, std::string version, std::string elements, std::string
encoding) ";

%feature("docstring")  sbol::Sequence::~Sequence "sbol::Sequence::~Sequence() ";


// File: classsbol_1_1_sequence_annotation.xml
%feature("docstring") sbol::SequenceAnnotation "";

%feature("docstring")  sbol::SequenceAnnotation::SequenceAnnotation "sbol::SequenceAnnotation::SequenceAnnotation(std::string
uri=DEFAULT_NS\"/SequenceAnnotation/example\") ";

%feature("docstring")  sbol::SequenceAnnotation::SequenceAnnotation "sbol::SequenceAnnotation::SequenceAnnotation(std::string uri_prefix,
std::string display_id, std::string version) ";

%feature("docstring")  sbol::SequenceAnnotation::~SequenceAnnotation "sbol::SequenceAnnotation::~SequenceAnnotation() ";


// File: classsbol_1_1_sequence_annotation_ext.xml
%feature("docstring") sbol::SequenceAnnotationExt "";

%feature("docstring")
sbol::SequenceAnnotationExt::SequenceAnnotationExt "sbol::SequenceAnnotationExt::SequenceAnnotationExt(std::string
uri_prefix=SBOL_URI\"/SequenceAnnotationExt\", std::string
id=\"example\", int start=-1, int end=-1, std::string
role=\"SO_0000001\") ";

%feature("docstring")
sbol::SequenceAnnotationExt::~SequenceAnnotationExt "sbol::SequenceAnnotationExt::~SequenceAnnotationExt() ";


// File: classsbol_1_1_sequence_constraint.xml
%feature("docstring") sbol::SequenceConstraint "";

%feature("docstring")  sbol::SequenceConstraint::SequenceConstraint "sbol::SequenceConstraint::SequenceConstraint(std::string
uri=DEFAULT_NS\"/SequenceConstraint/example\", std::string
subject=\"\", std::string object=\"\", std::string
restriction=SBOL_RESTRICTION_PRECEDES) ";

%feature("docstring")  sbol::SequenceConstraint::SequenceConstraint "sbol::SequenceConstraint::SequenceConstraint(std::string uri_prefix,
std::string display_id, std::string version, std::string subject,
std::string object, std::string restriction) ";

%feature("docstring")  sbol::SequenceConstraint::~SequenceConstraint "sbol::SequenceConstraint::~SequenceConstraint() ";


// File: classsbol_1_1_text_property.xml
%feature("docstring") sbol::TextProperty "";

%feature("docstring")  sbol::TextProperty::TextProperty "sbol::TextProperty::TextProperty(sbol_type type_uri, void
*property_owner, std::string initial_value=\"\") ";


// File: classsbol_1_1_top_level.xml
%feature("docstring") sbol::TopLevel "";

%feature("docstring")  sbol::TopLevel::TopLevel "sbol::TopLevel::TopLevel(std::string
uri=DEFAULT_NS\"/TopLevel/example\") ";

%feature("docstring")  sbol::TopLevel::TopLevel "sbol::TopLevel::TopLevel(std::string uri_prefix, std::string
display_id, std::string version) ";

%feature("docstring")  sbol::TopLevel::addToDocument "void
sbol::TopLevel::addToDocument(sbol::Document &) ";


// File: classsbol_1_1_u_r_i_property.xml
%feature("docstring") sbol::URIProperty "";

%feature("docstring")  sbol::URIProperty::URIProperty "sbol::URIProperty::URIProperty(sbol_type type_uri=UNDEFINED, void
*property_owner=NULL, std::string initial_value=\"\", ValidationRules
validation_rules={}) ";


// File: namespacesbol.xml
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
std::string resource_id, std::string &replacement_text) ";

%feature("docstring")  sbol::seek_element "void
sbol::seek_element(std::istringstream &xml_buffer, std::string uri) ";


%feature("docstring")  sbol::getCompliantURI "std::string
sbol::getCompliantURI(std::string uri_prefix, std::string display_id,
std::string sbol_class_name, std::string version) ";

%feature("docstring")  sbol::getClassName "std::string
sbol::getClassName(std::string type) ";

%feature("docstring")  sbol::getNameSpace "std::string
sbol::getNameSpace(std::string type) ";

%feature("docstring")  sbol::sbolRule10101 "void
sbol::sbolRule10101(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::sbolRule10102 "void
sbol::sbolRule10102(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::sbol_rule_10202 "void
sbol::sbol_rule_10202(void *sbol_obj, void *arg) ";

%feature("docstring")  sbol::libsbol_rule_1 "void
sbol::libsbol_rule_1(void *sbol_obj, void *arg) ";

