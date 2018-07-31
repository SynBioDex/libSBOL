
// File: index.xml

// File: classsbol_1_1_activity.xml


%feature("docstring") sbol::Activity "

A generated Entity is linked through a wasGeneratedBy relationship to an
Activity, which is used to describe how different Agents and other entities were
used. An Activity is linked through a qualifiedAssociation to Associations, to
describe the role of agents, and is linked through qualifiedUsage to Usages to
describe the role of other entities used as part of the activity. Moreover, each
Activity includes optional startedAtTime and endedAtTime properties. When using
Activity to capture how an entity was derived, it is expected that any
additional information needed will be attached as annotations. This may include
software settings or textual notes. Activities can also be linked together using
the wasInformedBy relationship to provide dependency without explicitly
specifying start and end times.  

Attributes
----------
* `startedAtTime` : `DateTimeProperty`  

* `endedAtTime` : `DateTimeProperty`  
    The endedAtTime property is OPTIONAL and contains a dateTime (see section
    Section 12.7) value, indicating when the activity ended.  

* `wasInformedBy` : `ReferencedObject`  
    The wasInformedBy property is OPTIONAL and contains a URI of another
    activity.  

* `associations` : `OwnedObject< Association >`  
    The qualifiedAssociation property is OPTIONAL and MAY contain a set of URIs
    that refers to Association.  

* `usages` : `OwnedObject< Usage >`  
    The qualifiedUsage property is OPTIONAL and MAY contain a set of URIs that
    refers to Usage objects.  

* `agent` : `OwnedObject< Agent >`  
    An Agent object may be specified here, and it will be synced with the
    Association::agent property.  

* `plan` : `OwnedObject< Plan >`  
    A Plan object may be specified here, and it will be synced with the
    Association::plan property.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/provo.h
";

%feature("docstring") sbol::Activity::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Activity::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Activity::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Activity::Activity "
`Activity(uri=\"example\", action_type=\"\", version=VERSION_STRING)`  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Activity::Activity "
`Activity(type, uri, action_type, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Activity::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Activity::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Activity::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Activity::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Activity::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Activity::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Activity::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Activity::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Activity::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Activity::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Activity::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Activity::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Activity::~Activity "
`~Activity()`  

The type property is an ontology term that designates an activity or stage in
the synthetic biology workflow, such as codon optimization or DNA assembly.  
";

%feature("docstring") sbol::Activity::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Activity::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Activity::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Activity::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Activity::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Activity::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Activity::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Activity::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Activity::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Activity::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

// File: classsbol_1_1_agent.xml


%feature("docstring") sbol::Agent "

Examples of agents are person, organisation or software. These agents should be
annotated with additional information, such as software version, needed to be
able to run the same software again.  

Attributes
----------
* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/provo.h
";

%feature("docstring") sbol::Agent::Agent "
`Agent(uri=\"example\", version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Agent::Agent "
`Agent(type, uri, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Agent::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Agent::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Agent::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Agent::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Agent::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Agent::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Agent::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Agent::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Agent::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Agent::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Agent::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Agent::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Agent::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Agent::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Agent::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Agent::~Agent "
`~Agent()`  
";

%feature("docstring") sbol::Agent::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Agent::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Agent::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Agent::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Agent::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Agent::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Agent::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Agent::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Agent::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Agent::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_aliased_property.xml


%feature("docstring") sbol::AliasedProperty "

Attributes
----------
* `alias` : `rdf_type`  

* `python_iter` : `std::vector< std::string >::iterator`  
";

%feature("docstring") sbol::AliasedProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::AliasedProperty::~AliasedProperty "
`~AliasedProperty()`  
";

%feature("docstring") sbol::AliasedProperty::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::AliasedProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::AliasedProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::AliasedProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::AliasedProperty::add "
`add(sbol_obj)`  
";

%feature("docstring") sbol::AliasedProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::AliasedProperty::find "
`find(uri) -> bool`  

Parameters
----------
* `uri` :  
    The full uniform resource identifier of the object to search for in this
    property  

Returns
-------
A boolean indicating whether found or not  
";

%feature("docstring") sbol::AliasedProperty::create "
`create(uri) -> SBOLClass &`  
";

%feature("docstring") sbol::AliasedProperty::set "
`set(sbol_obj)`  
";

%feature("docstring") sbol::AliasedProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::AliasedProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::AliasedProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::AliasedProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::AliasedProperty::__len__ "
`__len__() -> int`  
";

%feature("docstring") sbol::AliasedProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::AliasedProperty::clear "
`clear()`  

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::AliasedProperty::write "
`write()`  
";

%feature("docstring") sbol::AliasedProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::AliasedProperty::define "
`define(definition_object) -> SBOLClass &`  
";

%feature("docstring") sbol::AliasedProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::AliasedProperty::get "
`get(uri=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::AliasedProperty::getAll "
`getAll() -> std::vector< SBOLClass * >`  

Get all the objects contained in the property.  

Returns
-------
A vector of pointers to the objects  
";

%feature("docstring") sbol::AliasedProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::AliasedProperty::AliasedProperty "
`AliasedProperty(property_owner, sbol_uri, alias_uri, lower_bound, upper_bound,
    validation_rules)`  
";

%feature("docstring") sbol::AliasedProperty::remove "
`remove(uri) -> SBOLClass &`  

Remove an object from the list of objects.  

Parameters
----------
* `uri` :  
    This can be a displayId of the object or a full URI may be provided.  
";

%feature("docstring") sbol::AliasedProperty::remove "
`remove(index=0)`  

Remove an object from the list of objects and destroy it.  

Parameters
----------
* `index` :  
    A numerical index for the object.  
";

%feature("docstring") sbol::AliasedProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

// File: classsbol_1_1_analysis.xml


%feature("docstring") sbol::Analysis "

Attributes
----------
* `rawData` : `ReferencedObject`  
    A reference to a Test object which contains the raw data for an Analysis.  

* `dataFiles` : `ReferencedObject`  
    References to file Attachments which contain experimental data sets.  

* `dataSheet` : `ReferencedObject`  
    A reference to a datasheet file.  

* `consensusSequence` : `OwnedObject< Sequence >`  
    A sequence object that represents a consensus sequence from DNA sequencing
    data.  

* `fittedModel` : `OwnedObject< Model >`  
    A Model derived from fitting an experimental data set.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::Analysis::~Analysis "
`~Analysis()`  
";

%feature("docstring") sbol::Analysis::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Analysis::reportError "
`reportError() -> std::unordered_map< std::string, std::tuple< int, int, float >
    >`  
";

%feature("docstring") sbol::Analysis::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Analysis::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Analysis::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Analysis::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Analysis::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Analysis::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Analysis::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Analysis::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Analysis::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Analysis::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Analysis::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Analysis::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Analysis::reportCoverage "
`reportCoverage() -> std::unordered_map< std::string, std::tuple< int, int,
    float > >`  
";

%feature("docstring") sbol::Analysis::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Analysis::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Analysis::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Analysis::reportAmbiguity "
`reportAmbiguity() -> std::unordered_map< std::string, std::tuple< int, int,
    float > >`  
";

%feature("docstring") sbol::Analysis::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Analysis::verifyTarget "
`verifyTarget(consensus_sequence)`  

Compare a consensus Sequence to the target Sequence.  
";

%feature("docstring") sbol::Analysis::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Analysis::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Analysis::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Analysis::Analysis "
`Analysis(uri=\"example\", version=VERSION_STRING)`  

Construct a new Analysis object.  

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

%feature("docstring") sbol::Analysis::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Analysis::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Analysis::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Analysis::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Analysis::reportIdentity "
`reportIdentity() -> std::unordered_map< std::string, std::tuple< int, int,
    float > >`  
";

// File: classsbol_1_1_association.xml


%feature("docstring") sbol::Association "

An Association is linked to an Agent through the agent relationship. The
Association includes the hadRole property to qualify the role of the Agent in
the Activity.  

Attributes
----------
* `agent` : `ReferencedObject`  
    The agent property is REQUIRED and MUST contain a URI that refers to an
    Agent object.  

* `roles` : `URIProperty`  
    The hadRole property is REQUIRED and MUST contain a URI that refers to a
    particular term describing the usage of the agent.  

* `plan` : `ReferencedObject`  
    The hadPlan property is OPTIONAL and contains a URI that refers to a Plan.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/provo.h
";

%feature("docstring") sbol::Association::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Association::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Association::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Association::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Association::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Association::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Association::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Association::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Association::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Association::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Association::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Association::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Association::Association "
`Association(uri=\"example\", agent=\"\", role=\"\", version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Association::Association "
`Association(type, uri, agent, role, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Association::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Association::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Association::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Association::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Association::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Association::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Association::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Association::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Association::~Association "
`~Association()`  
";

// File: classsbol_1_1_attachment.xml


%feature("docstring") sbol::Attachment "

The Attachment class is a general container for data files, especially
experimental data files. Attachment is a TopLevel object, and any other TopLevel
object can refer to a list of attachments.  

Attributes
----------
* `source` : `URIProperty`  
    The source is a link to the external file and is REQUIRED.  

* `format` : `URIProperty`  

* `size` : `IntProperty`  

* `hash` : `TextProperty`  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/attachment.h
";

%feature("docstring") sbol::Attachment::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Attachment::~Attachment "
`~Attachment()`  
";

%feature("docstring") sbol::Attachment::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Attachment::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Attachment::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Attachment::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Attachment::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Attachment::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Attachment::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Attachment::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Attachment::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Attachment::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Attachment::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Attachment::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Attachment::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Attachment::Attachment "
`Attachment(uri=\"example\", source=\"\", version=VERSION_STRING)`  

Construct an Attachment.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `source` :  
    A file URI  
";

%feature("docstring") sbol::Attachment::Attachment "
`Attachment(type, uri, source, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Attachment::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Attachment::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Attachment::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Attachment::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Attachment::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Attachment::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Attachment::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Attachment::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Attachment::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Attachment::compare "
`compare(comparand) -> int`  

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

// File: classsbol_1_1_build.xml


%feature("docstring") sbol::Build "

A Build is a realization of a Design. For practical purposes, a Build can
represent a biological clone, a plasmid, or other laboratory sample. For a given
Design, there may be multiple Builds realized in the lab. A Build represents the
second step in libSBOL's formalized Design-Build-Test-Analyze workflow.  

Attributes
----------
* `design` : `ReferencedObject`  
    A reference to a Design object which represents the intended structure and
    function for this Build.  

* `structure` : `OwnedObject< ComponentDefinition >`  
    The experimentally verified structure of the construct as verified by DNA
    sequencing or other analysis.  

* `behavior` : `OwnedObject< ModuleDefinition >`  
    The observed behavior of the constructed system.  

* `sysbio_type` : `URIProperty`  

* `_structure` : `ReferencedObject`  

* `_behavior` : `ReferencedObject`  

* `built` : `URIProperty`  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/dbtl.h
";

%feature("docstring") sbol::Build::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Build::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Build::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Build::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Build::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Build::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Build::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Build::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Build::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Build::Build "
`Build(uri=\"example\", version=VERSION_STRING)`  

Constructs a new Build from scratch.  

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

%feature("docstring") sbol::Build::Build "
`Build(uri, structure, behavior, version=VERSION_STRING)`  

Constructs a new Build.  

The structure and behavior of the Build are initialized. A FunctionalComponent
is autoconstructed which correlates the structure and function.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `structure` :  
    A ComponentDefinition representing the experimentally verified structure of
    the construct as verified by DNA sequencing or other analysis  
* `function` :  
    A ModuleDefiniition representing the observed behavior of the constructed
    system  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::Build::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Build::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Build::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Build::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Build::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Build::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Build::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Build::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Build::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Build::~Build "
`~Build()`  
";

%feature("docstring") sbol::Build::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Build::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Build::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Build::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Build::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Build::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Build::cast "
`cast() -> SBOLClass &`  
";

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

Attributes
----------
* `members` : `URIProperty`  
    The members property of a Collection is OPTIONAL and MAY contain a set of
    URI references to zero or more TopLevel objects.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/collection.h
";

%feature("docstring") sbol::Collection::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Collection::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`Collection(uri=\"example\", version=VERSION_STRING)`  

Construct a Collection.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
";

%feature("docstring") sbol::Collection::Collection "
`Collection(type, uri, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Collection::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Collection::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Collection::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Collection::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Collection::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Collection::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Collection::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Collection::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Collection::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Collection::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Collection::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Collection::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Collection::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Collection::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Collection::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Collection::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Collection::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Collection::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Collection::~Collection "
`~Collection()`  
";

%feature("docstring") sbol::Collection::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Collection::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Collection::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Collection::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Collection::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_combinatorial_derivation.xml


%feature("docstring") sbol::CombinatorialDerivation "

A ComponentDeriviation specifies the composition of a combinatorial design or
variant library for common use cases in synthetic biology, such as tuning the
performance of a genetic circuit or biosynthetic pathway through combinatorial
DNA assembly and screening.  

Attributes
----------
* `strategy` : `URIProperty`  
    The `strategy` property is OPTIONAL and has a data type of URI.  

    Table 1 provides a list of REQUIRED strategy URIs. If the `strategy`
    property is not empty, then it MUST contain a URI from Table 1. This
    property recommends how many `ComponentDefinition` objects a user SHOULD
    derive from the `template` `ComponentDefinition`.
    Strategy URI  

    Description  

    http://sbols.org/v2#enumerate  

    A user SHOULD derive all `ComponentDefinition` objects with a unique
    substructure as specified by the `Component` objects contained by the
    `template` `ComponentDefinition` and the `VariableComponent` objects
    contained by the `CombinatorialDerivation`.  

    http://sbols.org/v2#sample  

    A user SHOULD derive a subset of all `ComponentDefinition` objects with a
    unique substructure as specified by the `Component` objects contained by the
    `template` `ComponentDefinition` and the `VariableComponent` objects
    contained by the `CombinatorialDerivation`. The manner in which this subset
    is chosen is for the user to decide.  

* `masterTemplate` : `ReferencedObject`  
    The `master` property is REQUIRED and MUST contain a URI that refers to a
    ComponentDefinition. This ComponentDefinition is expected to serve as a
    template for the derivation of new ComponentDefinition objects.
    Consequently, its components property SHOULD contain one or more Component
    objects that describe its substructure (referred to hereafter as template
    Component objects), and its sequenceConstraints property MAY also contain
    one or more SequenceConstraint objects that constrain this substructure.  

* `variableComponents` : `OwnedObject< VariableComponent >`  
    VariableComponent objects denote the choices available when deriving the
    library of variants specified by a CombinatorialDerivation.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/combinatorialderivation.h
";

%feature("docstring") sbol::CombinatorialDerivation::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::CombinatorialDerivation::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::CombinatorialDerivation::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::CombinatorialDerivation::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::CombinatorialDerivation::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::CombinatorialDerivation::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::CombinatorialDerivation::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::CombinatorialDerivation::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::CombinatorialDerivation::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::CombinatorialDerivation::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::CombinatorialDerivation::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::CombinatorialDerivation::CombinatorialDerivation "
`CombinatorialDerivation(uri=\"example\",
    strategy=\"http://sbols.org/v2#enumerate\", version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `strategy` :  
    A URI indicating SBOL_ENUMERATE or SBOL_SAMPLE  
";

%feature("docstring") sbol::CombinatorialDerivation::CombinatorialDerivation "
`CombinatorialDerivation(type, uri, strategy, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::CombinatorialDerivation::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::CombinatorialDerivation::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::CombinatorialDerivation::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::CombinatorialDerivation::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::CombinatorialDerivation::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::CombinatorialDerivation::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::CombinatorialDerivation::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::CombinatorialDerivation::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::CombinatorialDerivation::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::CombinatorialDerivation::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::CombinatorialDerivation::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::CombinatorialDerivation::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::CombinatorialDerivation::update_uri "
`update_uri()`  
";

// File: classsbol_1_1_component.xml


%feature("docstring") sbol::Component "

The Component class is used to compose ComponentDefinition objects into a
structural hierarchy. For example, the ComponentDefinition of a gene could
contain four Component objects: a promoter, RBS, CDS, and terminator. In turn,
the ComponentDefinition of the promoter Component could contain Component
objects defined as various operator sites.  

Attributes
----------
* `roles` : `URIProperty`  
    The expected purpose and function of a genetic part are described by the
    roles property of ComponentDefinition.  

    However, the same building block might be used for a different purpose in an
    actual design. In other words, purpose and function are sometimes determined
    by context. The roles property comprises an OPTIONAL set of zero or more
    role URIs describing the purpose or potential function of this Components
    included sub-ComponentDefinition in the context of its parent
    ComponentDefinition. If provided, these role URIs MUST identify terms from
    appropriate ontologies. Roles are not restricted to describing biological
    function; they may annotate a Components function in any domain for which
    an ontology exists. It is RECOMMENDED that these role URIs identify terms
    that are compatible with the type properties of both this Components parent
    ComponentDefinition and its included sub-ComponentDefinition. For example, a
    role of a Component which belongs to a ComponentDefinition of type DNA and
    includes a sub-ComponentDefinition of type DNA might refer to terms from the
    Sequence Ontology. See documentation for ComponentDefinition for a table of
    recommended ontology terms for roles.  

* `roleIntegration` : `URIProperty`  
    A roleIntegration specifies the relationship between a Component instances
    own set of roles and the set of roles on the included sub-
    ComponentDefinition.  

    The roleIntegration property has a data type of URI. A Component instance
    with zero roles MAY OPTIONALLY specify a roleIntegration. A Component
    instance with one or more roles MUST specify a roleIntegration from the
    table below If zero Component roles are given and no Component
    roleIntegration is given, then http://sbols.org/v2#mergeRoles is assumed. It
    is RECOMMENDED to specify a set of Component roles only if the integrated
    result set of roles would differ from the set of roles belonging to this
    Components included sub-ComponentDefinition.
    roleIntegration URI  

    Description  

    http://sbols.org/v2#overrideRoles  

    In the context of this Component, ignore any roles given for the included
    sub-ComponentDefinition.  


    Instead use only the set of zero or more roles given for this Component.  

    http://sbols.org/v2#mergeRoles  

    Use the union of the two sets: both the set of zero or more roles given for
    this Component as well  


    as the set of zero or more roles given for the included sub-
    ComponentDefinition.  

* `definition` : `ReferencedObject`  
    The definition property is a REQUIRED URI that refers to the
    ComponentDefinition of the ComponentInstance.  

    As described in the previous section, this ComponentDefinition effectively
    provides information about the types and roles of the ComponentInstance. The
    definition property MUST NOT refer to the same ComponentDefinition as the
    one that contains the ComponentInstance. Furthermore, ComponentInstance
    objects MUST NOT form a cyclical chain of references via their definition
    properties and the ComponentDefinition objects that contain them. For
    example, consider the ComponentInstance objects A and B and the
    ComponentDefinition objects X and Y . The reference chain X contains A, A
    isdefinedby Y, Y contains B, and B isdefinedby X iscyclical.  

* `access` : `URIProperty`  
    The access property is a REQUIRED URI that indicates whether the
    ComponentInstance can be referred to remotely by a MapsTo.  

    The value of the access property MUST be one of the following URIs.
    Access URI  

    Description  

    http://sbols.org/v2#public  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

    http://sbols.org/v2#private  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

* `mapsTos` : `OwnedObject< MapsTo >`  
    The mapsTos property is OPTIONAL and MAY contain a set of MapsTo objects
    that refer to and link together ComponentInstance objects (both Component
    objects and FunctionalComponent objects) within a larger design.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/component.h
";

%feature("docstring") sbol::Component::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Component::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Component::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Component::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Component::Component "
`Component(uri=\"example\", definition=\"\", access=SBOL_ACCESS_PUBLIC,
    version=VERSION_STRING)`  

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
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Component::~Component "
`~Component()`  
";

%feature("docstring") sbol::Component::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Component::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Component::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Component::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Component::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Component::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Component::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Component::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Component::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Component::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Component::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Component::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Component::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Component::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_component_definition.xml


%feature("docstring") sbol::ComponentDefinition "

The ComponentDefinition class represents the structural entities of a biological
design.  

The primary usage of this class is to represent structural entities with
designed sequences, such as DNA, RNA, and proteins, but it can also be used to
represent any other entity that is part of a design, such as small molecules,
proteins, and complexes  

Attributes
----------
* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that specifies the category of
    biochemical or physical entity (for example DNA, protein, or small molecule)
    that a ComponentDefinition object abstracts for the purpose of engineering
    design.  

    The types property of every ComponentDefinition MUST contain one or more
    URIs that MUST identify terms from appropriate ontologies, such as the
    BioPAX ontology or the ontology of Chemical Entities of Biological Interest.
    See the table below for examples.
    Type  

    URI for BioPAX Term  

    LibSBOL symbol  

    DNA  

    http://www.biopax.org/release/biopax-level3.owl#DnaRegion  

    BIOPAX_DNA  

    RNA  

    http://www.biopax.org/release/biopax-level3.owl#RnaRegion  

    BIOPAX_RNA  

    Protein  

    http://www.biopax.org/release/biopax-level3.owl#Protein  

    BIOPAX_PROTEIN  

    Small Molecule  

    http://www.biopax.org/release/biopax-level3.owl#SmallMolecule  

    BIOPAX_SMALL_MOLECULE  

    Complex  

    http://www.biopax.org/release/biopax-level3.owl#Complex  

    BIOPAX_COMPLEX  

* `roles` : `URIProperty`  
    The roles property is an OPTIONAL set of URIs that clarifies the potential
    function of the entity represented by a ComponentDefinition in a biochemical
    or physical context.  

    The roles property of a ComponentDefinition MAY contain one or more URIs
    that MUST identify terms from ontologies that are consistent with the types
    property of the ComponentDefinition. For example, the roles property of a
    DNA or RNA ComponentDefinition could contain URIs identifying terms from the
    Sequence Ontology (SO). See the table below for common examples
    Role  

    URI for Sequence Ontology Term  

    LibSBOL symbol  

    Miscellaneous  

    http://identifiers.org/so/SO:0000001  

    SO_MISC  

    Promoter  

    http://identifiers.org/so/SO:0000167  

    SO_PROMOTER  

    RBS  

    http://identifiers.org/so/SO:0000139  

    SO_RBS  

    CDS  

    http://identifiers.org/so/SO:0000316  

    SO_CDS  

    Terminator  

    http://identifiers.org/so/SO:0000141  

    SO_TERMINATOR  

    Gene  

    http://identifiers.org/so/SO:0000704  


    Operator  

    http://identifiers.org/so/SO:0000057  


    Engineered Gene  

    http://identifiers.org/so/SO:0000280  


    mRNA  

    http://identifiers.org/so/SO:0000234  


    Effector  

    http://identifiers.org/chebi/CHEBI:35224  
  

* `components` : `OwnedObject< Component >`  
    The components property is OPTIONAL and MAY specify a set of Component
    objects that are contained by the ComponentDefinition. The components
    properties of ComponentDefinition objects can be used to construct a
    hierarchy of Component and ComponentDefinition objects. If a
    ComponentDefinition in such a hierarchy refers to one or more Sequence
    objects, and there exist ComponentDefinition objects lower in the hierarchy
    that refer to Sequence objects with the same encoding, then the elements
    properties of these Sequence objects SHOULD be consistent with each other,
    such that well-defined mappings exist from the lower level elements to the
    higher level elements. This mapping is also subject to any restrictions on
    the positions of the Component objects in the hierarchy that are imposed by
    the SequenceAnnotation or SequenceConstraint objects contained by the
    ComponentDefinition objects in the hierarchy. The set of relations between
    Component and ComponentDefinition objects is strictly acyclic.  

* `sequences` : `ReferencedObject`  
    The sequences property is OPTIONAL and MAY include a URI that refer to a
    Sequence object. The referenced object defines the primary structure of the
    ComponentDefinition.  

* `sequence` : `OwnedObject< Sequence >`  

* `sequenceAnnotations` : `OwnedObject< SequenceAnnotation >`  
    The sequenceAnnotations property is OPTIONAL and MAY contain a set of
    SequenceAnnotation objects. Each SequenceAnnotation specifies and describes
    a potentially discontiguous region on the Sequence objects referred to by
    the ComponentDefinition.  

* `sequenceConstraints` : `OwnedObject< SequenceConstraint >`  
    The sequenceConstraints property is OPTIONAL and MAY contain a set of
    SequenceConstraint objects. These objects describe any restrictions on the
    relative, sequence-based positions and/or orientations of the Component
    objects contained by the ComponentDefinition. For example, the
    ComponentDefinition of a gene might specify that the position of its
    promoter Component precedes that of its CDS Component. This is particularly
    useful when a ComponentDefinition lacks a Sequence and therefore cannot
    specify the precise, sequence-based positions of its Component objects using
    SequenceAnnotation objects.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/componentdefinition.h
";

%feature("docstring") sbol::ComponentDefinition::participate "
`participate(species)`  

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

%feature("docstring") sbol::ComponentDefinition::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentDefinition::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentDefinition::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::ComponentDefinition::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::ComponentDefinition::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::ComponentDefinition::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentDefinition::getLastComponent "
`getLastComponent() -> Component &`  

Gets the last Component in a linear sequence.  

Returns
-------
The last component in sequential order  
";

%feature("docstring") sbol::ComponentDefinition::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::ComponentDefinition::hasDownstreamComponent "
`hasDownstreamComponent(current_component) -> int`  

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
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentDefinition::linearize "
`linearize(list_of_components={})`  
";

%feature("docstring") sbol::ComponentDefinition::linearize "
`linearize(list_of_uris)`  
";

%feature("docstring") sbol::ComponentDefinition::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ComponentDefinition::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::ComponentDefinition::updateSequence "
`updateSequence(composite_sequence=\"\") -> std::string`  

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
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ComponentDefinition::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::ComponentDefinition::hasUpstreamComponent "
`hasUpstreamComponent(current_component) -> int`  

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

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentDefinition::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentDefinition::addDownstreamFlank "
`addDownstreamFlank(target, elements)`  

This may be a useful method when building up SBOL representations of natural DNA
sequences.  

For example it is often necessary to specify components that are assumed to have
no meaningful role in the design, but are nevertheless important to fill in
regions of sequence. This method autoconstructs a ComponentDefinition and
Sequence object to create an arbitrary flanking sequence around design
Components. The new ComponentDefinition will have Sequence Ontology type of
flanking_sequence.  

Parameters
----------
* `target` :  
    The new flanking sequence will be placed downstream of the target  
* `elements` :  
    The primary sequence elements will be assigned to the autoconstructed
    Sequence object. The encoding is inferred  
";

%feature("docstring") sbol::ComponentDefinition::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::ComponentDefinition::addUpstreamFlank "
`addUpstreamFlank(target, elements)`  

This may be a useful method when building up SBOL representations of natural DNA
sequences.  

For example it is often necessary to specify components that are assumed to have
no meaningful role in the design, but are nevertheless important to fill in
regions of sequence. This method autoconstructs a ComponentDefinition and
Sequence object to create an arbitrary flanking sequence around design
Components. The new ComponentDefinition will have Sequence Ontology type of
flanking_region or SO:0000239  

Parameters
----------
* `target` :  
    The new flanking sequence will be placed upstream of the target  
* `elements` :  
    The primary sequence elements will be assigned to the autoconstructed
    Sequence object. The encoding is inferred  
";

%feature("docstring") sbol::ComponentDefinition::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentDefinition::build "
`build() -> ComponentDefinition &`  
";

%feature("docstring") sbol::ComponentDefinition::disassemble "
`disassemble(range_start=1)`  

Instantiates a Component for every SequenceAnnotation. When converting from a
flat GenBank file to a flat SBOL file, the result is a ComponentDefinition with
SequenceAnnotations. This method will convert the flat SBOL file into
hierarchical SBOL.  
";

%feature("docstring") sbol::ComponentDefinition::assemble "
`assemble(list_of_components, assembly_standard=\"\")`  

Assembles ComponentDefinitions into an abstraction hierarchy.  

The resulting data structure is a partial design, still lacking a primary
structure or explicit sequence. To form a primary structure out of the
ComponentDefinitions, call linearize after calling assemble. To fully realize
the target sequence, use Sequence::assemble().  

Parameters
----------
* `list_of_components` :  
    A list of subcomponents that will compose this ComponentDefinition  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::assemble "
`assemble(list_of_components, doc, assembly_standard=\"\")`  

Assembles ComponentDefinitions into an abstraction hierarchy.  

The resulting data structure is a partial design, still lacking a primary
structure or explicit sequence. To form a primary structure out of the
ComponentDefinitions, call linearize after calling assemble. To fully realize
the target sequence, use Sequence::assemble().  

Parameters
----------
* `list_of_components` :  
    A list of subcomponents that will compose this ComponentDefinition  
* `doc` :  
    The Document to which the assembled ComponentDefinitions will be added  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::assemble "
`assemble(list_of_uris, assembly_standard=\"\")`  

Assembles ComponentDefinitions into an abstraction hierarchy.  

The resulting data structure is a partial design, still lacking a primary
structure or explicit sequence. To form a primary structure out of the
ComponentDefinitions, call linearize after calling assemble. To fully realize
the target sequence, use Sequence::assemble().  

Parameters
----------
* `list_of_uris` :  
    A list of URIs for the constituent ComponentDefinitions, or displayIds if
    using SBOL-compliant URIs  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::getPrimaryStructure "
`getPrimaryStructure() -> std::vector< ComponentDefinition * >`  

Get the primary sequence of a design in terms of its sequentially ordered
Components.  
";

%feature("docstring") sbol::ComponentDefinition::isComplete "
`isComplete(msg) -> bool`  

Use this diagnose an incomplete design.  

Recursively checks if this ComponentDefinition defines a SequenceAnnotation and
Range for every Sequence. Completeness does not guarantee regularity  

Parameters
----------
* `msg` :  
    A message for diagnosing the irregularity, if any is found. The message is
    returned through an argument of type std::string&  

Returns
-------
true if the abstraction hierarchy is regular, false otherwise.  
";

%feature("docstring") sbol::ComponentDefinition::isComplete "
`isComplete() -> bool`  

Recursively verifies that the parent Document contains a ComponentDefinition and
Sequence for each and every ComponentDefinition in the abstraction hierarchy.  

If a ComponentDefinition is not complete, some objects are missing from the
Document or externally linked. Diagnose with isComplete(std::string &msg)  

Returns
-------
true if the abstraction hierarchy is complete, false otherwise.  
";

%feature("docstring") sbol::ComponentDefinition::~ComponentDefinition "
`~ComponentDefinition()`  
";

%feature("docstring") sbol::ComponentDefinition::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ComponentDefinition::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::ComponentDefinition::isRegular "
`isRegular(msg) -> bool`  

Use this diagnose an irregular design.  

Recursively checks if this ComponentDefinition defines a SequenceAnnotation and
Range for every Sequence. Regularity is more stringent than completeness. A
design must be complete to be regular.  

Parameters
----------
* `msg` :  
    A message for diagnosing the irregularity, if any is found. The message is
    returned through an argument of type std::string&  

Returns
-------
true if the abstraction hierarchy is regular, false otherwise.  
";

%feature("docstring") sbol::ComponentDefinition::isRegular "
`isRegular() -> bool`  

Recursively checks if this ComponentDefinition defines a SequenceAnnotation and
Range for every Sequence.  

Regularity is more stringent than completeness. A design must be complete to be
regular. If the Component is irregular, diagnose with isRegular(std::string
&msg)  

Returns
-------
true if the abstraction hierarchy is regular, false otherwise.  
";

%feature("docstring") sbol::ComponentDefinition::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::ComponentDefinition::getInSequentialOrder "
`getInSequentialOrder() -> std::vector< Component * >`  

Orders this ComponentDefinition's member Components into a linear arrangement
based on Sequence Constraints.  

Returns
-------
Primary sequence structure  
";

%feature("docstring") sbol::ComponentDefinition::assemblePrimaryStructure "
`assemblePrimaryStructure(primary_structure, assembly_standard=\"\")`  

Assembles ComponentDefinition into a linear primary structure.  

The resulting data structure is a partial design, still lacking an explicit
sequence. To fully realize the target sequence, use Sequence::assemble().  

Parameters
----------
* `primary_structure` :  
    A list of URIs for the constituent ComponentDefinitions, or displayIds if
    using SBOL-compliant URIs  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::assemblePrimaryStructure "
`assemblePrimaryStructure(primary_structure, assembly_standard=\"\")`  

Assembles ComponentDefinition into a linear primary structure.  

The resulting data structure is a partial design, still lacking an explicit
sequence. To fully realize the target sequence, use Sequence::assemble().  

Parameters
----------
* `list_of_components` :  
    A list of subcomponents that will compose this ComponentDefinition  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::assemblePrimaryStructure "
`assemblePrimaryStructure(primary_structure, doc, assembly_standard=\"\")`  

Assembles ComponentDefinition into a linear primary structure.  

The resulting data structure is a partial design, still lacking an explicit
sequence. To fully realize the target sequence, use Sequence::assemble().  

Parameters
----------
* `list_of_components` :  
    A list of subcomponents that will compose this ComponentDefinition  
* `doc` :  
    The Document to which the assembled ComponentDefinitions will be added  
* `assembly_standard` :  
    An optional argument such as IGEM_STANDARD_ASSEMBLY that affects how
    components are composed and the final target sequence  
";

%feature("docstring") sbol::ComponentDefinition::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ComponentDefinition::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::ComponentDefinition::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ComponentDefinition::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ComponentDefinition::getDownstreamComponent "
`getDownstreamComponent(current_component) -> Component &`  

Get the downstream Component.  

Returns
-------
The downstream component  
";

%feature("docstring") sbol::ComponentDefinition::getFirstComponent "
`getFirstComponent() -> Component &`  

Gets the first Component in a linear sequence.  

Returns
-------
The first component in sequential order  
";

%feature("docstring") sbol::ComponentDefinition::insertDownstream "
`insertDownstream(target, insert)`  

Insert a Component downstream of another in a primary sequence, shifting any
adjacent Components dowstream as well.  

Parameters
----------
* `target` :  
    The target Component will be upstream of the insert Component after this
    operation.  
* `insert` :  
    The insert Component is inserted downstream of the target Component.  
";

%feature("docstring") sbol::ComponentDefinition::compile "
`compile() -> std::string`  

Compiles an abstraction hierarchy of ComponentDefinitions into a nucleotide
sequence. If no Sequence object is associated with this ComponentDefinition, one
will be automatically instantiated.  
";

%feature("docstring") sbol::ComponentDefinition::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::ComponentDefinition::insertUpstream "
`insertUpstream(target, insert)`  

Insert a Component upstream of another in a primary sequence, shifting any
adjacent Components upstream as well.  

Parameters
----------
* `target` :  
    The target Component will be downstream of the insert Component after this
    operation.  
* `insert` :  
    The insert Component is inserted upstream of the target Component.  
";

%feature("docstring") sbol::ComponentDefinition::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::ComponentDefinition::applyToComponentHierarchy "
`applyToComponentHierarchy(callback_fn=NULL, user_data=NULL) -> std::vector<
    ComponentDefinition * >`  

Perform an operation on every Component in a structurally-linked hierarchy of
Components by applying a callback function.  

If no callback is specified, the default behavior is to return a pointer list of
each Component in the hierarchy.  

Parameters
----------
* `callback_fun` :  
    A pointer to a callback function with signature void
    callback_fn(ComponentDefinition *, void *).  
* `user_data` :  
    Arbitrary user data which can be passed in and out of the callback as an
    argument or return value.  

Returns
-------
Returns a flat list of pointers to all Components in the hierarchy.  
";

%feature("docstring") sbol::ComponentDefinition::getUpstreamComponent "
`getUpstreamComponent(current_component) -> Component &`  

Get the upstream Component.  

Returns
-------
The upstream component  
";

%feature("docstring") sbol::ComponentDefinition::ComponentDefinition "
`ComponentDefinition(uri=\"example\", type=BIOPAX_DNA, version=VERSION_STRING)`  

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

%feature("docstring") sbol::ComponentDefinition::ComponentDefinition "
`ComponentDefinition(type, uri, component_type, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `type` :  
    The RDF type for an extension class derived from this one  
";

// File: classsbol_1_1_component_instance.xml


%feature("docstring") sbol::ComponentInstance "

Attributes
----------
* `definition` : `ReferencedObject`  
    The definition property is a REQUIRED URI that refers to the
    ComponentDefinition of the ComponentInstance.  

    As described in the previous section, this ComponentDefinition effectively
    provides information about the types and roles of the ComponentInstance. The
    definition property MUST NOT refer to the same ComponentDefinition as the
    one that contains the ComponentInstance. Furthermore, ComponentInstance
    objects MUST NOT form a cyclical chain of references via their definition
    properties and the ComponentDefinition objects that contain them. For
    example, consider the ComponentInstance objects A and B and the
    ComponentDefinition objects X and Y . The reference chain X contains A, A
    isdefinedby Y, Y contains B, and B isdefinedby X iscyclical.  

* `access` : `URIProperty`  
    The access property is a REQUIRED URI that indicates whether the
    ComponentInstance can be referred to remotely by a MapsTo.  

    The value of the access property MUST be one of the following URIs.
    Access URI  

    Description  

    http://sbols.org/v2#public  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

    http://sbols.org/v2#private  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

* `mapsTos` : `OwnedObject< MapsTo >`  
    The mapsTos property is OPTIONAL and MAY contain a set of MapsTo objects
    that refer to and link together ComponentInstance objects (both Component
    objects and FunctionalComponent objects) within a larger design.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::ComponentInstance::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ComponentInstance::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentInstance::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ComponentInstance::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentInstance::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ComponentInstance::~ComponentInstance "
`~ComponentInstance()`  
";

%feature("docstring") sbol::ComponentInstance::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::ComponentInstance::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ComponentInstance::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::ComponentInstance::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::ComponentInstance::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::ComponentInstance::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::ComponentInstance::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::ComponentInstance::find_property "
`find_property(uri) -> SBOLObject *`  

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
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ComponentInstance::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::ComponentInstance::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentInstance::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ComponentInstance::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::ComponentInstance::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_config.xml


%feature("docstring") sbol::Config "

A class which contains global configuration variables for the libSBOL
environment. Intended to be used like a static class, configuration variables
are accessed through the Config::setOptions and Config::getOptions methods.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/config.h
";

%feature("docstring") sbol::Config::setOption "
`setOption(option, value)`  

Configure options for libSBOL.  

Access online validation and conversion.
Option  

Description  

Values  

homespace  

Enable validation and conversion requests through the online validator  

http://examples.org  

sbol_compliant_uris  

Enables autoconstruction of SBOL-compliant URIs from displayIds  

True or False  

sbol_typed_uris  

Include the SBOL type in SBOL-compliant URIs  

True or False  

output_format  

File format for serialization  

True or False  

validate  

Enable validation and conversion requests through the online validator  

True or False  

validator_url  

The http request endpoint for validation  

A valid URL, set to  http://www.async.ece.utah.edu/sbol-validator/endpoint.php
by default  

language  

File format for conversion  

SBOL2, SBOL1, FASTA, GenBank  

test_equality  

Report differences between two files  

True or False  

check_uri_compliance  

If set to false, URIs in the file will not be checked for compliance  
with the SBOL specification  

True or False  

check_completeness  

If set to false, not all referenced objects must be described within  
the given main_file  

True or False  

check_best_practices  

If set to true, the file is checked for the best practice rules set  
in the SBOL specification  

True or False  

fail_on_first_error  

If set to true, the validator will fail at the first error  

True or False  

provide_detailed_stack_trace  

If set to true (and failOnFirstError is true) the validator will  
provide a stack trace for the first validation error  

True or False  

uri_prefix  

Required for conversion from FASTA and GenBank to SBOL1 or SBOL2,  
used to generate URIs  

True or False  

version  

Adds the version to all URIs and to the document  

A valid Maven version string  

return_file  

Whether or not to return the file contents as a string  

True or False  

Parameters
----------
* `option` :  
    The option key  
* `value` :  
    The option value  
";

%feature("docstring") sbol::Config::setOption "
`setOption(option, value)`  
";

%feature("docstring") sbol::Config::setOption "
`setOption(option, value)`  
";

%feature("docstring") sbol::Config::Config "
`Config()`  
";

%feature("docstring") sbol::Config::getOption "
`getOption(option) -> std::string`  

Get current option value for online validation and conversion.  

Parameters
----------
* `option` :  
    The option key  
";

// File: classsbol_1_1_cut.xml


%feature("docstring") sbol::Cut "

The Cut class specifies a location between two coordinates of a Sequence's
elements. class Cut : public Location.  

Attributes
----------
* `at` : `IntProperty`  
    This property specifies the location between this nucleotide coordinate (or
    other sequence element) and the nucleotide coordinate immediately following
    it. When equal to zero, the specified region is immediately before the first
    nucleotide or character in the elements.  

* `orientation` : `URIProperty`  
    The orientation indicates how a region of double-stranded DNA represented by
    the parent SequenceAnnotation and its associated Component are oriented.  

    The orientation may be one of the following values. By default it is set to
    SBOL_ORIENTATION_INLINE.
    Orientation URI  

    libSBOL Symbol  

    http://sbols.org/v2#inline  

    SBOL_ORIENTATION_INLINE  

    http://sbols.org/v2#reverseComplement  

    SBOL_ORIENTATION_REVERSE_COMPLEMENT  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/location.h
";

%feature("docstring") sbol::Cut::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Cut::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Cut::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Cut::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Cut::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Cut::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Cut::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Cut::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Cut::~Cut "
`~Cut()`  
";

%feature("docstring") sbol::Cut::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Cut::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Cut::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Cut::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Cut::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Cut::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Cut::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Cut::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Cut::Cut "
`Cut(uri=\"example\", at=0)`  

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

%feature("docstring") sbol::Cut::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Cut::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Cut::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Cut::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_date_time_property.xml


%feature("docstring") sbol::DateTimeProperty "

Contains a DateTime string following XML Schema.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::DateTimeProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::DateTimeProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::DateTimeProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::DateTimeProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::DateTimeProperty::stampTime "
`stampTime() -> std::string`  

Set this property with the current time.  
";

%feature("docstring") sbol::DateTimeProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::DateTimeProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::DateTimeProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::DateTimeProperty::DateTimeProperty "
`DateTimeProperty(property_owner, type_uri, lower_bound, upper_bound,
    initial_value)`  

Initialize the DateTime.  

Conformance to XML DateTime schema is validated upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
";

%feature("docstring") sbol::DateTimeProperty::DateTimeProperty "
`DateTimeProperty(property_owner, type_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::DateTimeProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::DateTimeProperty::write "
`write()`  
";

%feature("docstring") sbol::DateTimeProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::DateTimeProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::DateTimeProperty::getAll "
`getAll() -> std::vector< std::string >`  
";

%feature("docstring") sbol::DateTimeProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::DateTimeProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::DateTimeProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::DateTimeProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::DateTimeProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::DateTimeProperty::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::DateTimeProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::DateTimeProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::DateTimeProperty::get "
`get() -> std::string`  

Basic getter for all SBOL literal properties.  

Returns
-------
A string literal  
";

// File: classsbol_1_1_design.xml


%feature("docstring") sbol::Design "

This class represents a biological Design. A Design is a conceptual
representation of a biological system that a synthetic biologist intends to
build. A Design is the first object created in libSBOL's formalized Design-
Build-Test-Analysis workflow.  

Attributes
----------
* `structure` : `OwnedObject< ComponentDefinition >`  
    The target biological structure for synthesis or other molecular assembly.  

* `function` : `OwnedObject< ModuleDefinition >`  
    The intended function and predicted behavior of the Design object.  

* `characterization` : `ReferencedObject`  
    A reference to an Analysis or multiple Analysis objects that contain
    characterization data, previously verified experimental knowledge, or
    explanatory models that inform a Design.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/dbtl.h
";

%feature("docstring") sbol::Design::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Design::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Design::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Design::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Design::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Design::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Design::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Design::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Design::Design "
`Design(uri=\"example\", version=VERSION_STRING)`  

Construct a new Design from scratch.  

The structure and function of the Design are not initialized.  

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

%feature("docstring") sbol::Design::Design "
`Design(uri, structure, function, version=VERSION_STRING)`  

Constructs a new Design.  

The structure and function of the Design are initialized. A FunctionalComponent
is autoconstructed which correlates the structure and function.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `structure` :  
    A ComponentDefinition representing the structural aspects of the Design  
* `function` :  
    A ModuleDefiniition representing the functional aspects of the Design  
* `version` :  
    An arbitrary version string. If SBOLCompliance is enabled, this should be a
    Maven version string of the form \"major.minor.patch\".  
";

%feature("docstring") sbol::Design::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Design::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Design::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Design::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Design::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Design::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Design::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Design::~Design "
`~Design()`  
";

%feature("docstring") sbol::Design::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Design::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Design::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Design::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Design::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Design::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Design::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Design::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Design::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Design::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

// File: classsbol_1_1_document.xml


%feature("docstring") sbol::Document "

Read and write SBOL using a Document class. The Document is a container for
Components, Modules, and all other SBOLObjects.  

Attributes
----------
* `designs` : `OwnedObject< Design >`  

* `builds` : `OwnedObject< Build >`  

* `tests` : `OwnedObject< Test >`  

* `analyses` : `OwnedObject< Analysis >`  

* `componentDefinitions` : `OwnedObject< ComponentDefinition >`  

* `moduleDefinitions` : `OwnedObject< ModuleDefinition >`  

* `models` : `OwnedObject< Model >`  

* `sequences` : `OwnedObject< Sequence >`  

* `collections` : `OwnedObject< Collection >`  

* `activities` : `OwnedObject< Activity >`  

* `plans` : `OwnedObject< Plan >`  

* `agents` : `OwnedObject< Agent >`  

* `attachments` : `OwnedObject< Attachment >`  

* `combinatorialderivations` : `OwnedObject< CombinatorialDerivation >`  

* `implementations` : `OwnedObject< Implementation >`  

* `sampleRosters` : `OwnedObject< SampleRoster >`  

* `citations` : `URIProperty`  

* `keywords` : `URIProperty`  

* `python_iter` : `iterator`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/document.h
";

%feature("docstring") sbol::Document::request_validation "
`request_validation(sbol) -> std::string`  
";

%feature("docstring") sbol::Document::readString "
`readString(sbol)`  

Convert text in SBOL into data objects.  

Parameters
----------
* `sbol` :  
    A string formatted in SBOL  
";

%feature("docstring") sbol::Document::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Document::addModel "
`addModel(sbol_obj)`  
";

%feature("docstring") sbol::Document::close "
`close(uri=\"\")`  

Delete all objects in this Document and destroy the Document.  
";

%feature("docstring") sbol::Document::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Document::summary "
`summary() -> std::string`  

Get a summary of objects in the Document, including SBOL core object and custom
annotation objects.  
";

%feature("docstring") sbol::Document::Document "
`Document()`  

Construct a Document. The Document is a container for Components, Modules, and
all other SBOLObjects.  
";

%feature("docstring") sbol::Document::Document "
`Document(filename)`  
";

%feature("docstring") sbol::Document::generate "
`generate(world, sbol_serializer, sbol_buffer, sbol_buffer_len, ios, base_uri)`  

Generates rdf/xml.  

author: KC generates rdf/xml  
";

%feature("docstring") sbol::Document::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Document::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Document::add "
`add(sbol_obj)`  

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
`add(sbol_objects)`  

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

%feature("docstring") sbol::Document::add "
`add(sbol_obj)`  
";

%feature("docstring") sbol::Document::add "
`add(sbol_obj)`  
";

%feature("docstring") sbol::Document::add "
`add(sbol_obj)`  
";

%feature("docstring") sbol::Document::add "
`add(sbol_obj)`  
";

%feature("docstring") sbol::Document::write "
`write(filename) -> std::string`  

Serialize all objects in this Document to an RDF/XML file.  

Parameters
----------
* `filename` :  
    The full name of the file you want to write (including file extension)  

Returns
-------
A string with the validation results, or empty string if validation is disabled  
";

%feature("docstring") sbol::Document::~Document "
`~Document()`  
";

%feature("docstring") sbol::Document::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Document::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Document::addModuleDefinition "
`addModuleDefinition(sbol_obj)`  
";

%feature("docstring") sbol::Document::validate "
`validate() -> std::string`  

Run validation on this Document via the online validation tool.  

Returns
-------
A string containing a message with the validation results  

author: KC  
";

%feature("docstring") sbol::Document::read "
`read(filename)`  

Read an RDF/XML file and attach the SBOL objects to this Document.  

Existing contents of the Document will be wiped.  

Parameters
----------
* `filename` :  
    The full name of the file you want to read (including file extension)  
";

%feature("docstring") sbol::Document::addNamespace "
`addNamespace(ns, prefix)`  

Add a new namespace to this Document.  

Parameters
----------
* `ns` :  
    The namespace, eg. http://sbols.org/v2#  
* `prefix` :  
    The namespace prefix, eg. sbol  
";

%feature("docstring") sbol::Document::search_metadata "
`search_metadata(role, type, name, collection) -> std::string`  
";

%feature("docstring") sbol::Document::getNamespaces "
`getNamespaces() -> std::vector< std::string >`  

Returns
-------
A vector of namespaces Get namespaces contained in this Document  
";

%feature("docstring") sbol::Document::query_repository "
`query_repository(command) -> std::string`  
";

%feature("docstring") sbol::Document::getAll "
`getAll() -> std::vector< SBOLClass * >`  

Retrieve a vector of objects from the Document.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL objects  
";

%feature("docstring") sbol::Document::end "
`end() -> iterator`  
";

%feature("docstring") sbol::Document::find "
`find(uri) -> SBOLObject *`  

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
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Document::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::Document::request_comparison "
`request_comparison(diff_file) -> std::string`  

Perform comparison on Documents using the online validation tool.  

This is for cross-validation of SBOL documents with libSBOLj. Document
comparison can also be performed using the built-in compare method.  

Returns
-------
The comparison results  
";

%feature("docstring") sbol::Document::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Document::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Document::copy "
`copy(ns=\"\", doc=NULL, version=\"\") -> Document &`  
";

%feature("docstring") sbol::Document::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Document::addSequence "
`addSequence(sbol_obj)`  
";

%feature("docstring") sbol::Document::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Document::size "
`size() -> int`  

Get the total number of objects in the Document, including SBOL core object and
custom annotation objects.  
";

%feature("docstring") sbol::Document::writeString "
`writeString() -> std::string`  

Convert data objects in this Document into textual SBOL.  
";

%feature("docstring") sbol::Document::append "
`append(filename)`  

Read an RDF/XML file and attach the SBOL objects to this Document.  

New objects will be added to the existing contents of the Document  

Parameters
----------
* `filename` :  
    The full name of the file you want to read (including file extension)  
";

%feature("docstring") sbol::Document::get "
`get(uri) -> SBOLClass &`  

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

%feature("docstring") sbol::Document::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Document::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Document::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Document::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Document::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Document::countTriples "
`countTriples() -> int`  
";

%feature("docstring") sbol::Document::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Document::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Document::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Document::addComponentDefinition "
`addComponentDefinition(sbol_obj)`  
";

// File: classsbol_1_1_enzyme_catalysis_interaction.xml


%feature("docstring") sbol::EnzymeCatalysisInteraction "

Attributes
----------
* `enzyme` : `AliasedProperty< FunctionalComponent >`  

* `substrates` : `AliasedProperty< FunctionalComponent >`  

* `products` : `AliasedProperty< FunctionalComponent >`  

* `cofactors` : `AliasedProperty< FunctionalComponent >`  

* `sideproducts` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::EnzymeCatalysisInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::EnzymeCatalysisInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::EnzymeCatalysisInteraction "
`EnzymeCatalysisInteraction(uri, enzyme, substrates, products)`  
";

%feature("docstring") sbol::EnzymeCatalysisInteraction::EnzymeCatalysisInteraction "
`EnzymeCatalysisInteraction(uri, enzyme, substrates, products, cofactors,
    sideproducts)`  
";

// File: classsbol_1_1_float_property.xml


%feature("docstring") sbol::FloatProperty "

FloatProperty objects are used to contain floats.  

They can be used as member objects inside custom SBOL Extension classes.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::FloatProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::FloatProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::FloatProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::FloatProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::FloatProperty::FloatProperty "
`FloatProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules, initial_value)`  

Initialize the IntProperty with a value.  

Validation rules are checked upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::FloatProperty::FloatProperty "
`FloatProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules)`  

Initialize a FloatProperty without a value.  

No validation rules are run upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::FloatProperty::FloatProperty "
`FloatProperty(property_owner, type_uri, lower_bound, upper_bound,
    initial_value)`  
";

%feature("docstring") sbol::FloatProperty::FloatProperty "
`FloatProperty(property_owner, type_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::FloatProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::FloatProperty::write "
`write()`  
";

%feature("docstring") sbol::FloatProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::FloatProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::FloatProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::FloatProperty::get "
`get() -> double`  

Get the float value.  

Returns
-------
An integer  
";

%feature("docstring") sbol::FloatProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::FloatProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::FloatProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::FloatProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::FloatProperty::getAll "
`getAll() -> std::vector< double >`  
";

%feature("docstring") sbol::FloatProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::FloatProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::FloatProperty::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::FloatProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::FloatProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::FloatProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

// File: classsbol_1_1_functional_component.xml


%feature("docstring") sbol::FunctionalComponent "

The FunctionalComponent class is used to specify the functional usage of a
ComponentDefinition inside a ModuleDefinition. The ModuleDefinition describes
how the that describes how the FunctionalComponent interacts with others and
summarizes their aggregate function.  

Attributes
----------
* `direction` : `URIProperty`  
    Each FunctionalComponent MUST specify via the direction property whether it
    serves as an input, output, both, or neither for its parent ModuleDefinition
    object.  

    The value for this property MUST be one of the URIs given in the table
    below.
    Direction URI  

    Description  

    LibSBOL Symbol  

    http://sbols.org/v2#in  

    Indicates that the FunctionalComponent is an input.  

    SBOL_DIRECTION_IN  

    http://sbols.org/v2#out  

    Indicates that the FunctionalComponent is an output.  

    SBOL_DIRECTION_OUT  

    http://sbols.org/v2#inout  

    Indicates that the FunctionalComponent is both an input and output  

    SBOL_DIRECTION_IN_OUT  

    http://sbols.org/v2#none  

    Indicates that the FunctionalComponent is neither an input or output.  

    SBOL_DIRECTION_NONE  

* `definition` : `ReferencedObject`  
    The definition property is a REQUIRED URI that refers to the
    ComponentDefinition of the ComponentInstance.  

    As described in the previous section, this ComponentDefinition effectively
    provides information about the types and roles of the ComponentInstance. The
    definition property MUST NOT refer to the same ComponentDefinition as the
    one that contains the ComponentInstance. Furthermore, ComponentInstance
    objects MUST NOT form a cyclical chain of references via their definition
    properties and the ComponentDefinition objects that contain them. For
    example, consider the ComponentInstance objects A and B and the
    ComponentDefinition objects X and Y . The reference chain X contains A, A
    isdefinedby Y, Y contains B, and B isdefinedby X iscyclical.  

* `access` : `URIProperty`  
    The access property is a REQUIRED URI that indicates whether the
    ComponentInstance can be referred to remotely by a MapsTo.  

    The value of the access property MUST be one of the following URIs.
    Access URI  

    Description  

    http://sbols.org/v2#public  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

    http://sbols.org/v2#private  

    The ComponentInstance MAY be referred to by remote MapsTo objects  

* `mapsTos` : `OwnedObject< MapsTo >`  
    The mapsTos property is OPTIONAL and MAY contain a set of MapsTo objects
    that refer to and link together ComponentInstance objects (both Component
    objects and FunctionalComponent objects) within a larger design.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/component.h
";

%feature("docstring") sbol::FunctionalComponent::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::FunctionalComponent::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::FunctionalComponent::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::FunctionalComponent::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::FunctionalComponent::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::FunctionalComponent::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::FunctionalComponent::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::FunctionalComponent::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::FunctionalComponent::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::FunctionalComponent::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::FunctionalComponent::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::FunctionalComponent::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::FunctionalComponent::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::FunctionalComponent::~FunctionalComponent "
`~FunctionalComponent()`  
";

%feature("docstring") sbol::FunctionalComponent::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::FunctionalComponent::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::FunctionalComponent::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::FunctionalComponent::FunctionalComponent "
`FunctionalComponent(uri=\"example\", definition=\"\",
    access=SBOL_ACCESS_PUBLIC, direction=SBOL_DIRECTION_NONE,
    version=VERSION_STRING)`  

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

%feature("docstring") sbol::FunctionalComponent::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::FunctionalComponent::isMasked "
`isMasked() -> int`  

Used to tell if a FunctionalComponent is linked to an equivalent
FunctionalComponent in another ModuleDefinition.  

Returns
-------
1 if the FunctionalComponent has been over-rided by another FunctionalComponent,
0 if it hasn't.  
";

%feature("docstring") sbol::FunctionalComponent::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::FunctionalComponent::connect "
`connect(interface_component)`  

This method connects module inputs and outputs.  

This convenience method auto-constructs a MapsTo object. See Biosystem Design
for an example  

Parameters
----------
* `interface_component` :  
    An input or output component from another ModuleDefinition that corresponds
    with this component.  
";

%feature("docstring") sbol::FunctionalComponent::mask "
`mask(masked_component)`  

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

%feature("docstring") sbol::FunctionalComponent::override "
`override(masked_component)`  

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
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_gene_production_interaction.xml


%feature("docstring") sbol::GeneProductionInteraction "

Attributes
----------
* `gene` : `AliasedProperty< FunctionalComponent >`  

* `product` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::GeneProductionInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::GeneProductionInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::GeneProductionInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::GeneProductionInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::GeneProductionInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GeneProductionInteraction::GeneProductionInteraction "
`GeneProductionInteraction(uri, gene, product)`  
";

%feature("docstring") sbol::GeneProductionInteraction::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::GeneProductionInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::GeneProductionInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::GeneProductionInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::GeneProductionInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::GeneProductionInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GeneProductionInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::GeneProductionInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::GeneProductionInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::GeneProductionInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::GeneProductionInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::GeneProductionInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::GeneProductionInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::GeneProductionInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GeneProductionInteraction::update_uri "
`update_uri()`  
";

// File: classsbol_1_1_generic_location.xml


%feature("docstring") sbol::GenericLocation "

the GenericLocation class is included as a starting point for specifying regions
on Sequence objects with encoding properties other than IUPAC and potentially
nonlinear structure. This class can also be used to set the orientation of a
SequenceAnnotation and any associated Component when their parent
ComponentDefinition is a partial design that lacks a Sequence.  

Attributes
----------
* `orientation` : `URIProperty`  
    The orientation indicates how a region of double-stranded DNA represented by
    the parent SequenceAnnotation and its associated Component are oriented.  

    The orientation may be one of the following values. By default it is set to
    SBOL_ORIENTATION_INLINE.
    Orientation URI  

    libSBOL Symbol  

    http://sbols.org/v2#inline  

    SBOL_ORIENTATION_INLINE  

    http://sbols.org/v2#reverseComplement  

    SBOL_ORIENTATION_REVERSE_COMPLEMENT  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/location.h
";

%feature("docstring") sbol::GenericLocation::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::GenericLocation::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::GenericLocation::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::GenericLocation::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::GenericLocation::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::GenericLocation::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::GenericLocation::~GenericLocation "
`~GenericLocation()`  
";

%feature("docstring") sbol::GenericLocation::GenericLocation "
`GenericLocation(uri=\"example\")`  

Construct a GenericLocation.  

If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create <
GenericLocation > instead.  

Parameters
----------
* `uri` :  
    If operating in open-world mode, this should be a full URI including a
    scheme, namespace, and identifier. If SBOLCompliance configuration is
    enabled, then this argument is simply the displayId for the new object and a
    full URI will automatically be constructed.  
";

%feature("docstring") sbol::GenericLocation::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::GenericLocation::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::GenericLocation::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::GenericLocation::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::GenericLocation::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::GenericLocation::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GenericLocation::find_property "
`find_property(uri) -> SBOLObject *`  

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
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GenericLocation::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::GenericLocation::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::GenericLocation::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::GenericLocation::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::GenericLocation::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::GenericLocation::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

// File: classsbol_1_1_identified.xml


%feature("docstring") sbol::Identified "

All SBOL-defined classes are directly or indirectly derived from the Identified
abstract class.  

An Identified object is identified using a Uniform Resource Identifier (URI), a
unique string that identifies and refers to a specific object in an SBOL
document or in an online resource such as a DNA repository.  

Attributes
----------
* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/identified.h
";

%feature("docstring") sbol::Identified::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Identified::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Identified::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Identified::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Identified::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Identified::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Identified::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Identified::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Identified::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Identified::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Identified::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Identified::~Identified "
`~Identified()`  
";

%feature("docstring") sbol::Identified::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Identified::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Identified::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Identified::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Identified::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Identified::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Identified::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Identified::Identified "
`Identified(type_uri=SBOL_IDENTIFIED, uri=\"example\", version=VERSION_STRING)`  
";

%feature("docstring") sbol::Identified::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Identified::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

// File: classsbol_1_1_implementation.xml


%feature("docstring") sbol::Implementation "

An Implementation represents a real, physical instance of a synthetic biological
construct which may be associated with a laboratory sample. An Implementation
may be linked back to its original design (either a ModuleDefinition or
ComponentDefinition) using the wasDerivedFrom property inherited from the
Identified superclass.  

Attributes
----------
* `built` : `URIProperty`  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/implementation.h
";

%feature("docstring") sbol::Implementation::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Implementation::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Implementation::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Implementation::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Implementation::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Implementation::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Implementation::Implementation "
`Implementation(uri=\"example\", version=VERSION_STRING)`  

Construct an Implementation.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Implementation::Implementation "
`Implementation(type, uri, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Implementation::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Implementation::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Implementation::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Implementation::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Implementation::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Implementation::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Implementation::~Implementation "
`~Implementation()`  
";

%feature("docstring") sbol::Implementation::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Implementation::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Implementation::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Implementation::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Implementation::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Implementation::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Implementation::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Implementation::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Implementation::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Implementation::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Implementation::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Implementation::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

// File: classsbol_1_1_interaction.xml


%feature("docstring") sbol::Interaction "

The Interaction class provides more detailed descriptionof how the
FunctionalComponents are intended to work together. For example, this class can
be used to represent different forms of genetic regulation (e.g.,
transcriptional activation or repression), processes from the central dogma of
biology (e.g. transcription and translation), and other basic molecular
interactions (e.g., non-covalent binding or enzymatic phosphorylation).  

Attributes
----------
* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/interaction.h
";

%feature("docstring") sbol::Interaction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Interaction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Interaction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Interaction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Interaction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Interaction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

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
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Interaction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Interaction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Interaction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Interaction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Interaction::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Interaction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Interaction::Interaction "
`Interaction(uri=\"example\", interaction_type=SBO_INTERACTION)`  

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

%feature("docstring") sbol::Interaction::Interaction "
`Interaction(type, uri, interaction_type)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Interaction::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Interaction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Interaction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Interaction::~Interaction "
`~Interaction()`  
";

%feature("docstring") sbol::Interaction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Interaction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Interaction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Interaction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::IntProperty::IntProperty "
`IntProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules, initial_value)`  

Initialize the IntProperty with a value.  

Validation rules are checked upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::IntProperty::IntProperty "
`IntProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules)`  

Initialize an IntProperty without a value.  

No validation rules are run upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::IntProperty::IntProperty "
`IntProperty(property_owner, type_uri, lower_bound, upper_bound, initial_value)`  
";

%feature("docstring") sbol::IntProperty::IntProperty "
`IntProperty(property_owner, type_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::IntProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::IntProperty::get "
`get() -> int`  

Get the integer value.  

Returns
-------
An integer  
";

%feature("docstring") sbol::IntProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::IntProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::IntProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::IntProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::IntProperty::getAll "
`getAll() -> std::vector< int >`  
";

%feature("docstring") sbol::IntProperty::write "
`write()`  
";

%feature("docstring") sbol::IntProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::IntProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::IntProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::IntProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::IntProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::IntProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::IntProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::IntProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::IntProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::IntProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::IntProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::IntProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::IntProperty::getUpperBound "
`getUpperBound() -> char`  
";

// File: classsbol_1_1_owned_object_1_1iterator.xml


%feature("docstring") sbol::OwnedObject::iterator "

Provides iterator functionality for SBOL properties that contain multiple
objects.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/object.h
";

%feature("docstring") sbol::OwnedObject::iterator::iterator "
`iterator(i_object=std::vector< SBOLObject *>::iterator())`  
";

// File: classsbol_1_1_search_response_1_1iterator.xml


%feature("docstring") sbol::SearchResponse::iterator "

Provides iterator functionality for SBOL properties that contain multiple
objects.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/partshop.h
";

%feature("docstring") sbol::SearchResponse::iterator::iterator "
`iterator(i_object=std::vector< Identified *>::iterator())`  
";

// File: classsbol_1_1_document_1_1iterator.xml


%feature("docstring") sbol::Document::iterator "

Iterate through TopLevel objects in a Document.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/document.h
";

%feature("docstring") sbol::Document::iterator::iterator "
`iterator(i_obj=std::unordered_map< std::string, sbol::SBOLObject
    *>::iterator())`  
";

// File: classsbol_1_1_property_1_1iterator.xml


%feature("docstring") sbol::Property::iterator "

Provides iterator functionality for SBOL properties that contain multiple
values.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/property.h
";

%feature("docstring") sbol::Property::iterator::iterator "
`iterator(i_str=std::vector< std::string >::iterator())`  
";

// File: classsbol_1_1_location.xml


%feature("docstring") sbol::Location "

The Location class specifies the strand orientation of a Component and can be
further extended by the Range, Cut, and GenericLocation classes.  

Attributes
----------
* `orientation` : `URIProperty`  
    The orientation indicates how a region of double-stranded DNA represented by
    the parent SequenceAnnotation and its associated Component are oriented.  

    The orientation may be one of the following values. By default it is set to
    SBOL_ORIENTATION_INLINE.
    Orientation URI  

    libSBOL Symbol  

    http://sbols.org/v2#inline  

    SBOL_ORIENTATION_INLINE  

    http://sbols.org/v2#reverseComplement  

    SBOL_ORIENTATION_REVERSE_COMPLEMENT  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/location.h
";

%feature("docstring") sbol::Location::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Location::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Location::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Location::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Location::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Location::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Location::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Location::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Location::Location "
`Location(type=SBOL_LOCATION, uri=\"example\",
    orientation=SBOL_ORIENTATION_INLINE)`  
";

%feature("docstring") sbol::Location::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Location::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Location::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Location::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Location::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Location::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Location::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Location::~Location "
`~Location()`  
";

%feature("docstring") sbol::Location::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Location::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Location::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Location::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Location::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
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

Attributes
----------
* `refinement` : `URIProperty`  
    Each MapsTo object MUST specify the relationship between its local and
    remote ComponentInstance objects using one of the REQUIRED refinement URIs
    provided in the table below.  

    Refinement URI  

    libSBOL Symbol  

    Description  

    http://sbols.org/v2#useRemote  

    SBOL_REFINEMENT_USE_REMOTE  

    All references to the local ComponentInstance MUST dereference to the  
    remote ComponentInstance instead.  

    http://sbols.org/v2#useLocal  

    SBOL_REFINEMENT_USE_LOCAL  

    In the context of the ComponentDefinition or ModuleDefinition that contains  
    the owner of the MapsTo, all references to the remote ComponentInstance  
    MUST dereference to the local ComponentInstance instead.  

    http://sbols.org/v2#verifyIdentical  

    SBOL_REFINEMENT_VERIFY_IDENTICAL  

    The definition properties of the local and remoteComponentInstance objects  
    MUST refer to the same ComponentDefinition.  

    http://sbols.org/v2#merge  

    SBOL_REFINEMENT_MERGE_DESCRIPTION  

    In the context of the ComponentDefinition or ModuleDefinition that  
    contains the owner of the MapsTo, all references to the local  
    ComponentInstance or the remote ComponentInstance MUST dereference  
    to both objects.  

* `local` : `ReferencedObject`  
    The identity of the lower level ComponentInstance.  

* `remote` : `ReferencedObject`  
    The identity of the higher level ComponentInstance.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/mapsto.h
";

%feature("docstring") sbol::MapsTo::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::MapsTo::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::MapsTo::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::MapsTo::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::MapsTo::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::MapsTo::~MapsTo "
`~MapsTo()`  
";

%feature("docstring") sbol::MapsTo::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::MapsTo::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::MapsTo::MapsTo "
`MapsTo(uri=\"example\", local=\"\", remote=\"\",
    refinement=SBOL_REFINEMENT_VERIFY_IDENTICAL)`  

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

%feature("docstring") sbol::MapsTo::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::MapsTo::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::MapsTo::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::MapsTo::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::MapsTo::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::MapsTo::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::MapsTo::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::MapsTo::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::MapsTo::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::MapsTo::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::MapsTo::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::MapsTo::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::MapsTo::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_model.xml


%feature("docstring") sbol::Model "

The purpose of the Model class is to serve as a placeholder for an external
computational model and provide additional meta-data to enable better reasoning
about the contents of this model.  

In this way, there is minimal duplication of standardization efforts and users
of SBOL can formalize the function of a ModuleDefinition in the language of
their choice.  

Attributes
----------
* `source` : `URIProperty`  
    The source property is REQUIRED and MUST contain a URI reference to the
    source file for a model.  

* `language` : `URIProperty`  
    The language property is REQUIRED and MUST contain a URI that specifies the
    language in which the model is implemented.  

    It is RECOMMENDED that this URI refer to a term from the EMBRACE Data and
    Methods (EDAM) ontology. The Table below provides a list of terms from this
    ontology and their URIs. If the language property of a Model is well-
    described by one these terms, then it MUST contain the URI for this term as
    its value.
    Model Language  

    URI for EDAM Term  

    libSBOL Symbol  

    SBML  

    http://identifiers.org/edam/format_2585  

    EDAM_SBML  

    CellML  

    http://identifiers.org/edam/format_3240  

    EDAM_CELLML  

    BioPAX  

    http://identifiers.org/edam/format_3156  

    EDAM_BIOPAX  

* `framework` : `URIProperty`  
    Model Language  

    URI for SBO Term  

    libSBOL Symbol  

    Continuous  

    http://identifiers.org/biomodels.sbo/SBO:0000062  

    SBO_CONTINUOUS  

    Discrete  

    http://identifiers.org/biomodels.sbo/SBO:0000063  

    SBO_DISCRETE  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/model.h
";

%feature("docstring") sbol::Model::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Model::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Model::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Model::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

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
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Model::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Model::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Model::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Model::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Model::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Model::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Model::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Model::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Model::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Model::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Model::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Model::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Model::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Model::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Model::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Model::~Model "
`~Model()`  
";

%feature("docstring") sbol::Model::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Model::Model "
`Model(uri=\"example\", source=\"\", language=EDAM_SBML,
    framework=SBO_CONTINUOUS, version=VERSION_STRING)`  

Construct a Model.  

Parameters
----------
* `source` :  
    A URI reference to the model file  
* `An` :  
    EDAM ontology term that specifies the language in which the model was
    implemented  
* `An` :  
    SBOL ontology term that specifies whether the model is continuous, discrete,
    or other modeling technique  
";

%feature("docstring") sbol::Model::Model "
`Model(type, uri, source, language, framework, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Model::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Model::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Model::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Model::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

// File: classsbol_1_1_module.xml


%feature("docstring") sbol::Module "

The Module class represents a submodule of a ModuleDefinition within a
hierarchical design.  

Attributes
----------
* `definition` : `ReferencedObject`  
    The definition property is a REQUIRED URI that refers to the
    ModuleDefinition for the Module.  

* `mapsTos` : `OwnedObject< MapsTo >`  
    The mapsTos property is an OPTIONAL set of MapsTo objects that refer to and
    link ComponentInstance objects together within the heterarchy of Module,
    ModuleDefinition, ComponentInstance, and ComponentDefinition objects.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/module.h
";

%feature("docstring") sbol::Module::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Module::compare "
`compare(comparand) -> int`  

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
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Module::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Module::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Module::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Module::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Module::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Module::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Module::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Module::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Module::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Module::~Module "
`~Module()`  
";

%feature("docstring") sbol::Module::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Module::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Module::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`Module(uri=\"example\", definition=\"\", version=VERSION_STRING)`  

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

%feature("docstring") sbol::Module::Module "
`Module(type, uri, definition, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Module::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Module::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Module::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Module::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Module::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

// File: classsbol_1_1_module_definition.xml


%feature("docstring") sbol::ModuleDefinition "

The ModuleDefinition class represents a grouping of structural and functional
entities in a biological design. The primary usage of this class is to assert
the molecular interactions and abstract function of its child entities.  

Attributes
----------
* `roles` : `URIProperty`  
    The roles property is an OPTIONAL set of URIs that clarifies the intended
    function of a ModuleDefinition. These URIs might identify descriptive
    biological roles, such as metabolic pathway and signaling cascade, but
    they can also identify identify logical roles, such as inverter or AND
    gate, or other abstract roles for describing the function of design.
    Interpretation of the meaning of such roles currently depends on the
    software tools that read and write them.  

* `modules` : `OwnedObject< Module >`  
    The modules property is OPTIONAL and MAY specify a set of Module objects
    contained by the ModuleDefinition. While the ModuleDefinition class is
    analogous to a specification sheet for a system of interacting biological
    elements, the Module class represents the occurrence of a particular
    subsystem within the system. Hence, this class allows a system design to
    include multiple instances of a subsystem, all defined by reference to the
    same ModuleDefinition. For example, consider the ModuleDefinition for a
    network of two-input repressor devices in which the particular repressors
    have not been chosen yet. This ModuleDefinition could contain multiple
    Module objects that refer to the same ModuleDefinition of an abstract two-
    input repressor device. Note that the set of relations between Module and
    ModuleDefinition objects is strictly acyclic.  

* `interactions` : `OwnedObject< Interaction >`  
    The interactions property is OPTIONAL and MAY specify a set of Interaction
    objects within the ModuleDefinition. The Interaction class provides an
    abstract, machine-readable representation of entity behavior within a
    ModuleDefinition. Each Interaction contains Participation objects that
    indicate the roles of the FunctionalComponent objects involved in the
    Interaction.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  
    The functionalComponents property is OPTIONAL and MAY specify a set of
    FunctionalComponent objects contained by the ModuleDefinition. Just as a
    Module represents an instance of a subsystem in the overall system
    represented by a ModuleDefinition, a FunctionalComponent represents an
    instance of a structural entity (represented by a ComponentDefinition) in
    the system. This concept allows a ModuleDefinition to assert different
    interactions for separate copies of the same structural entity if needed.
    For example, a ModuleDefinition might contain multiple FunctionalComponent
    objects that refer to the same promoter ComponentDefinition, but assert
    different interactions for these promoter copies based on their separate
    positions in another ComponentDefinition that represents the structure of
    the entire system.  

* `models` : `ReferencedObject`  
    The models property is OPTIONAL and MAY specify a set of URI references to
    Model objects. Model objects are placeholders that link ModuleDefinition
    objects to computational models of any format. A ModuleDefinition object can
    link to more than one Model since each might encode system behavior in a
    different way or at a different level of detail.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/moduledefinition.h
";

%feature("docstring") sbol::ModuleDefinition::override "
`override(highlevel, lowlevel)`  

Overrides a low-level component in an abstract sub-Module with a high-level
component in a parent ModuleDefinition, for example when overriding an abstract
template Module with explicit components.  

Parameters
----------
* `highlevel` :  
    A high-level FunctionalComponent  
* `lowlevel` :  
    A low-level FunctionalComponent in a nested sub-Module  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::ModuleDefinition::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::ModuleDefinition::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ModuleDefinition::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::ModuleDefinition::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::ModuleDefinition::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ModuleDefinition::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::ModuleDefinition::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::ModuleDefinition::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::ModuleDefinition::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::ModuleDefinition::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ModuleDefinition::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::ModuleDefinition::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::ModuleDefinition::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::ModuleDefinition::ModuleDefinition "
`ModuleDefinition(uri=\"example\", version=VERSION_STRING)`  

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

%feature("docstring") sbol::ModuleDefinition::ModuleDefinition "
`ModuleDefinition(sbol_type_uri, uri, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::ModuleDefinition::connect "
`connect(output, input)`  

Connects the output of a sub-Module with the input of another sub-Module.  

Auto-constructs MapsTo objects.  

Parameters
----------
* `output` :  
    A FunctionalComponent configured as a Module output (see setOutput)  
* `input` :  
    A FunctionalComponent configured as a Module input (see setInput)  
";

%feature("docstring") sbol::ModuleDefinition::assemble "
`assemble(list_of_modules)`  

Assemble a high-level ModuleDefinition from lower-level submodules.  

Autoconstructs Module objects in the process.  

Parameters
----------
* `list_of_modules` :  
    A list of pointers to the submodule ModuleDefinitions  
";

%feature("docstring") sbol::ModuleDefinition::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`setInput(input) -> FunctionalComponent &`  

Defines an input for a sub-Module.  

Useful for top-down assembly of Modules and sub-Modules. If a
FunctionalComponent with the given definition does not exist yet, one will be
autoconstructed. Otherwise the FunctionalComponent with the given definition
will be inferred. Be warned that this inference may fail if there is more than
one FunctionalComponent with the same definition.  

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

%feature("docstring") sbol::ModuleDefinition::setInput "
`setInput(input)`  

Configures a FunctionalComponent as an input for a Module.  

Useful for bottom-up assembly of Modules and sub-Modules  

Parameters
----------
* `input` :  
    The FunctionalComponent that will be configured  
";

%feature("docstring") sbol::ModuleDefinition::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::ModuleDefinition::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::ModuleDefinition::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::ModuleDefinition::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::ModuleDefinition::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::ModuleDefinition::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::ModuleDefinition::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::ModuleDefinition::~ModuleDefinition "
`~ModuleDefinition()`  
";

%feature("docstring") sbol::ModuleDefinition::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::ModuleDefinition::setOutput "
`setOutput(output) -> FunctionalComponent &`  

Defines an output for a sub-Module.  

Useful for top-down assembly of Modules and sub-Modules. If a
FunctionalComponent with the given definition does not exist yet, one will be
autoconstructed. Otherwise the FunctionalComponent with the given definition
will be inferred. Be warned that this inference may fail if there is more than
one FunctionalComponent with the same definition.  

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

%feature("docstring") sbol::ModuleDefinition::setOutput "
`setOutput(output)`  

Configures a FunctionalComponent as an output for a Module.  

Useful for bottom-up assembly of Modules and sub-Modules.  

Parameters
----------
* `output` :  
    The FunctionalComponent that will be configured  
";

%feature("docstring") sbol::ModuleDefinition::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::ModuleDefinition::addToDocument "
`addToDocument(arg1)`  
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

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/object.h
";

%feature("docstring") sbol::OwnedObject::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
`OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound,
    validation_rules, first_object)`  

Initialize a container and put the first object in it.  

Validation rules are checked upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
`OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound,
    validation_rules)`  

Initialize a container property.  

No validation rules are run upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
`OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound, first_object)`  
";

%feature("docstring") sbol::OwnedObject::OwnedObject "
`OwnedObject(property_owner, sbol_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::OwnedObject::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::OwnedObject::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::OwnedObject::write "
`write()`  
";

%feature("docstring") sbol::OwnedObject::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::OwnedObject::remove "
`remove(uri) -> SBOLClass &`  

Remove an object from the list of objects.  

Parameters
----------
* `uri` :  
    This can be a displayId of the object or a full URI may be provided.  
";

%feature("docstring") sbol::OwnedObject::remove "
`remove(index=0)`  

Remove an object from the list of objects and destroy it.  

Parameters
----------
* `index` :  
    A numerical index for the object.  
";

%feature("docstring") sbol::OwnedObject::get "
`get(uri=\"\") -> SBOLClass &`  

Get the child object.  

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

templateparam
-------------
* `SBOLClass` :  
    The type of the child object  

Parameters
----------
* `uri` :  
    The URI of the child object  

Returns
-------
A reference to the child object By default returns the first object in this
OwnedObject container property  
";

%feature("docstring") sbol::OwnedObject::get "
`get(uri=\"\") -> SBOLSubClass &`  

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

%feature("docstring") sbol::OwnedObject::getAll "
`getAll() -> std::vector< SBOLClass * >`  

Get all the objects contained in the property.  

Returns
-------
A vector of pointers to the objects  
";

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> SBOLClass &`  

Autoconstructs a child object and attaches it to the parent object.  

The new object will be constructed with default values specified in the
constructor for this type of object. If SBOLCompliance is enabled, the child
object's identity will be constructed using the supplied displayId argument.
Otherwise, the user should supply a full URI.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object that will be created  

Parameters
----------
* `uri` :  
    If SBOLCompliance is enabled, this should be the displayId for the new child
    object. If not enabled, this should be a full raw URI.  

Returns
-------
A reference to the child object  check uniqueness of URI in Document  
";

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> SBOLSubClass &`  

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

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> Build &`  
";

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> Test &`  
";

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> Build &`  
";

%feature("docstring") sbol::OwnedObject::create "
`create(uri) -> Test &`  
";

%feature("docstring") sbol::OwnedObject::set "
`set(sbol_obj)`  

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

%feature("docstring") sbol::OwnedObject::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::OwnedObject::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::OwnedObject::set "
`set(new_value)`  
";

%feature("docstring") sbol::OwnedObject::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::OwnedObject::clear "
`clear()`  

Remove all children objects from the parent and destroy them.  
";

%feature("docstring") sbol::OwnedObject::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::OwnedObject::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::OwnedObject::size "
`size() -> int`  
";

%feature("docstring") sbol::OwnedObject::find "
`find(uri) -> bool`  

Parameters
----------
* `uri` :  
    The full uniform resource identifier of the object to search for in this
    property  

Returns
-------
A boolean indicating whether found or not  
";

%feature("docstring") sbol::OwnedObject::define "
`define(definition_object) -> SBOLClass &`  

Autoconstructs a child object and attaches it to the parent object.  

Additionally, it sets the definition property of the child object, for example,
in the case of creating Components, FunctionalComponents, and Modules. The new
object will be constructed with default values specified in the constructor for
this type of object. If SBOLCompliance is enabled, the child object's identity
will be constructed using the supplied displayId argument. Otherwise, the user
should supply a full URI.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object that will be created  

Parameters
----------
* `definition_object` :  
    The returned object will reference the definition_object in its definition
    property.  

Returns
-------
A reference to the child object  check uniqueness of URI in Document  
";

%feature("docstring") sbol::OwnedObject::end "
`end() -> iterator`  
";

%feature("docstring") sbol::OwnedObject::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::OwnedObject::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::OwnedObject::add "
`add(sbol_obj)`  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object contained in this OwnedObject property  

Parameters
----------
* `sbol_obj` :  
    A child object to add to this container property. Adds a child object to the
    parent object. This method always appends another object to those already
    contained in this OwnedObject property. In SBOLCompliant mode, the create
    method is preferred  
";

%feature("docstring") sbol::OwnedObject::add "
`add(new_value)`  

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

Attributes
----------
* `roles` : `URIProperty`  
    The roles property is an OPTIONAL set of URIs that describes the behavior of
    a Participation (and by extension its referenced FunctionalComponent) in the
    context of its parent Interaction.  

    The roles property MAY contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the participant role
    branch of the SBO. The table below provides a list of possible SBO terms for
    the roles property and their corresponding URIs.
    Role  

    Systems Biology Ontology Term  

    LibSBOL Symbol  

    Inhibitor  

    http://identifiers.org/biomodels.sbo/SBO:0000020  

    SBO_INHIBITOR  

    Stimulator  

    http://identifiers.org/biomodels.sbo/SBO:0000459  

    SBO_STIMULATOR  

    Reactant  

    http://identifiers.org/biomodels.sbo/SBO:0000010  

    SBO_REACTANT  

    Product  

    http://identifiers.org/biomodels.sbo/SBO:0000011  

    SBO_PRODUCT  

    Ligand  

    http://identifiers.org/biomodels.sbo/SBO:0000280  

    SBO_LIGAND  

    Non-covalent Complex  

    http://identifiers.org/biomodels.sbo/SBO:0000253  

    SBO_NONCOVALENT_COMPLEX  

    If a Participation is well described by one of the terms from this table
    then its roles property MUST contain the URI that identifies this term.
    Lastly, if the roles property of a Participation contains multiple URIs,
    then they MUST identify non-conflicting terms. For example, the SBO terms
    stimulator and inhibitor would conflict.  

* `participant` : `ReferencedObject`  
    The participant property MUST specify precisely one FunctionalComponent
    object that plays the designated role in its parent Interaction object.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/participation.h
";

%feature("docstring") sbol::Participation::~Participation "
`~Participation()`  
";

%feature("docstring") sbol::Participation::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Participation::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Participation::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Participation::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Participation::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Participation::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Participation::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Participation::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Participation::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Participation::define "
`define(species, role=\"\")`  
";

%feature("docstring") sbol::Participation::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Participation::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Participation::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Participation::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Participation::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Participation::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Participation::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Participation::Participation "
`Participation(uri=\"example\", participant=\"\", version=VERSION_STRING)`  

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
`Participation(uri, species, version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `species` :  
    A ComponentDefinition that represents one of the participating species in
    the parent Interaction  
";

%feature("docstring") sbol::Participation::Participation "
`Participation(type, uri, participant, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Participation::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Participation::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Participation::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Participation::find_property "
`find_property(uri) -> SBOLObject *`  

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

// File: classsbol_1_1_part_shop.xml


%feature("docstring") sbol::PartShop "

A class which provides an API front-end for online bioparts repositories.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/partshop.h
";

%feature("docstring") sbol::PartShop::pull "
`pull(uri, doc)`  

Retrieve an object from an online resource.  

Parameters
----------
* `uri` :  
    The identity of the SBOL object you want to retrieve  
* `doc` :  
    A document to add the data to  
";

%feature("docstring") sbol::PartShop::pull "
`pull(uris, doc)`  

Retrieve an object from an online resource.  

Parameters
----------
* `uris` :  
    A vector of URIs for multiple SBOL objects you want to retrieve  
* `doc` :  
    A document to add the data to  
";

%feature("docstring") sbol::PartShop::pull "
`pull(uri, doc, recursive=true)`  
";

%feature("docstring") sbol::PartShop::pull "
`pull(uri, doc, recursive)`  
";

%feature("docstring") sbol::PartShop::pull "
`pull(uri, doc, recursive)`  
";

%feature("docstring") sbol::PartShop::login "
`login(email, password=\"\")`  

In order to submit to a PartShop, you must login first.  

Register on SynBioHub to obtain account credentials.  

Parameters
----------
* `email` :  
    The email associated with the user's SynBioHub account  
* `password` :  
    The user's password  
";

%feature("docstring") sbol::PartShop::submit "
`submit(doc, collection=\"\", overwrite=0) -> std::string`  

Submit an SBOL Document to SynBioHub.  

Parameters
----------
* `doc` :  
    The Document to submit  
* `collection` :  
    The URI of an SBOL Collection to which the Document contents will be
    uploaded  
* `overwrite` :  
    An integer code: 0(default) - do not overwrite, 1 - overwrite, 2 - merge  
";

%feature("docstring") sbol::PartShop::addSynBioHubAnnotations "
`addSynBioHubAnnotations(doc)`  
";

%feature("docstring") sbol::PartShop::search "
`search(search_text, object_type, property_uri, offset=0, limit=25) ->
    SearchResponse &`  

An EXACT search.  

Scan the parts repository for objects that exactly match the specified criteria.
In most uses of this function, LibSBOL's built-in RDF type constants (see
constants.h) will come in handy. For instance, searching for all
SBOL_COMPONENT_DEFINITION of type BIOPAX_DNA. (These constants follow a fairly
systematic and consistent naming scheme (see constants.h). The number of records
returned in the search is specified by offset and limit parameters.  

Parameters
----------
* `search_text` :  
    This may be a literal text value or it may be a URI.  
* `object_type` :  
    The RDF type of an SBOL object. See constants.h. For example,
    SBOL_COMPONENT_DEFINITION  
* `property_uri` :  
    The RDF type of an SBOL property. Specifies which field of an SBOL object to
    search. For example, SBOL_ROLES. Refer to constants.h  
* `offset` :  
    The index of the first record to return. This parameter is indexed starting
    from zero.  
* `limit` :  
    The total count number of records to return  

Returns
-------
Metadata formatted as a string encoding JSON.  
";

%feature("docstring") sbol::PartShop::search "
`search(search_text, object_type=SBOL_COMPONENT_DEFINITION, offset=0, limit=25)
    -> SearchResponse &`  

A GENERAL search.  

Search name, description, and displayId properties for a match to the search
text, including matches to substrings of the property value. The type of object
to search for can be further restricted by use of the second parameter, though
this is set to SBOL_COMPONENT_DEFINITION by default. See constants.h for more of
libSBOL's built-in RDF type constants. These constants follow a fairly
predictable and consistent naming scheme. The number of records returned in the
search is specified by offset and limit parameters.  

Parameters
----------
* `search_text` :  
    A snippet of text to search for in a property's value.  
* `object_type` :  
    The RDF type of an SBOL object. See constants.h. For example,
    SBOL_COMPONENT_DEFINITION by default.  
* `offset` :  
    The index of the first record to return. This parameter is indexed starting
    from zero.  
* `limit` :  
    The total count number of records to return  

Returns
-------
Metadata formatted as a string encoding JSON.  
";

%feature("docstring") sbol::PartShop::search "
`search(q) -> SearchResponse &`  

Perform an ADVANCED search using a SearchQuery object.  

Parameters
----------
* `search_query` :  
    A map of string key-value pairs. Keys are objectType, sbolTag, collection,
    dcterms:tag, namespace/tag, offset, limit.  

Returns
-------
Search metadata A vector of maps with key-value pairs.  
";

%feature("docstring") sbol::PartShop::searchRootCollections "
`searchRootCollections() -> std::string`  

Returns all Collections that are not members of any other Collections.  

Parameters
----------
* `doc` :  
    A Document to add the Collections to  
";

%feature("docstring") sbol::PartShop::attachFile "
`attachFile(topleveluri, filename)`  

Upload and attach a file to a TopLevel object in a PartShop.  

Parameters
----------
* `top_level_uri` :  
    The identity of the object to which the file will be attached  
* `file_name` :  
    A path to the file attachment  
";

%feature("docstring") sbol::PartShop::count "
`count() -> int`  

Return the count of objects contained in a PartShop.  

templateparam
-------------
* `SBOLClass` :  
    The type of SBOL object, usually a ComponentDefinition  
";

%feature("docstring") sbol::PartShop::getURL "
`getURL() -> std::string`  

Returns the network address of the PartShop.  

Returns
-------
The URL of the online repository  
";

%feature("docstring") sbol::PartShop::searchCount "
`searchCount(search_text, object_type, property_uri) -> int`  

Returns the number of search records for an EXACT search matching the given
criteria.  

Returns
-------
An integer count.  
";

%feature("docstring") sbol::PartShop::searchCount "
`searchCount(search_text, object_type=SBOL_COMPONENT_DEFINITION) -> int`  

Returns the number of search records for a general search matching the given
criteria.  

Returns
-------
An integer count.  
";

%feature("docstring") sbol::PartShop::searchCount "
`searchCount(q) -> int`  

Returns the number of search records matching the given criteria for an ADVANCED
search.  

Parameters
----------
* `search_query` :  
    A map of string key-value pairs. See SearchQuery for required and optional
    criteria.  

Returns
-------
An integer count.  
";

%feature("docstring") sbol::PartShop::searchSubCollections "
`searchSubCollections(uri) -> std::string`  

Returns all Collections that are members of the Collection specified by its URI.  

Parameters
----------
* `uri` :  
    The URI of a Collection of Collections  
* `doc` :  
    A Document to add the subcollections to  
";

%feature("docstring") sbol::PartShop::downloadAttachment "
`downloadAttachment(attachment_uri, path=\".\")`  

Download a file attached to a TopLevel object in an online repository.  

Parameters
----------
* `attachment_uri` :  
    The full URI of the attached object  
* `path` :  
    The target path to which the file will be downloaded  
";

%feature("docstring") sbol::PartShop::PartShop "
`PartShop(url)`  

Construct an interface to an instance of SynBioHub or other parts repository.  

Parameters
----------
* `The` :  
    URL of the online repository  
";

// File: classsbol_1_1_plan.xml


%feature("docstring") sbol::Plan "

Examples of agents are person, organisation or software. These agents should be
annotated with additional information, such as software version, needed to be
able to run the same software again.  

Attributes
----------
* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/provo.h
";

%feature("docstring") sbol::Plan::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Plan::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Plan::Plan "
`Plan(uri=\"example\", version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Plan::Plan "
`Plan(type, uri, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Plan::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Plan::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Plan::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Plan::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Plan::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Plan::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Plan::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Plan::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Plan::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Plan::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Plan::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Plan::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Plan::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Plan::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Plan::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Plan::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Plan::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Plan::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Plan::~Plan "
`~Plan()`  
";

%feature("docstring") sbol::Plan::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Plan::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Plan::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Plan::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Plan::generate "
`generate() -> SBOLClass &`  
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

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/property.h
";

%feature("docstring") sbol::Property::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::Property::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::Property::size "
`size() -> int`  
";

%feature("docstring") sbol::Property::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::Property::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::Property::Property "
`Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules,
    initial_value)`  

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
`Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules,
    initial_value)`  
";

%feature("docstring") sbol::Property::Property "
`Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules,
    initial_value)`  
";

%feature("docstring") sbol::Property::Property "
`Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)`  
";

%feature("docstring") sbol::Property::write "
`write()`  
";

%feature("docstring") sbol::Property::~Property "
`~Property()`  
";

%feature("docstring") sbol::Property::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::Property::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::Property::end "
`end() -> iterator`  
";

%feature("docstring") sbol::Property::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::Property::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::Property::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::Property::set "
`set(new_value)`  
";

%feature("docstring") sbol::Property::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::Property::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::Property::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::Property::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::Property::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::Property::validate "
`validate(arg=NULL)`  
";

// File: classsbol_1_1_range.xml


%feature("docstring") sbol::Range "

A Range object specifies a region via discrete, inclusive start and end
positions that correspond to indices for characters in the elements String of a
Sequence. Note that the index of the first location is 1, as is typical practice
in biology, rather than 0, as is typical practice in computer science.  

Attributes
----------
* `start` : `IntProperty`  
    Specifies the inclusive starting position of a sequence region. It must be 1
    or greater.  

* `end` : `IntProperty`  
    Specifies the inclusive end position of a sequence region. It must be equal
    to or greater than the start.  

* `orientation` : `URIProperty`  
    The orientation indicates how a region of double-stranded DNA represented by
    the parent SequenceAnnotation and its associated Component are oriented.  

    The orientation may be one of the following values. By default it is set to
    SBOL_ORIENTATION_INLINE.
    Orientation URI  

    libSBOL Symbol  

    http://sbols.org/v2#inline  

    SBOL_ORIENTATION_INLINE  

    http://sbols.org/v2#reverseComplement  

    SBOL_ORIENTATION_REVERSE_COMPLEMENT  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/location.h
";

%feature("docstring") sbol::Range::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Range::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Range::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Range::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Range::adjoins "
`adjoins(comparand) -> int`  

Indicate if these Ranges represent adjacent intervals.  

Another Range object  

Returns
-------
1 if these Ranges adjoin or border each other, 0 if they are separated by an
intervening Range  
";

%feature("docstring") sbol::Range::follows "
`follows(comparand) -> int`  

Calculates how many bases separate these Ranges  Another Range object.  

Returns
-------
The number of bases by which this Range follows the comparand, or 0 if it does
not follow  
";

%feature("docstring") sbol::Range::length "
`length() -> int`  

Returns the length of a Range.  
";

%feature("docstring") sbol::Range::contains "
`contains(comparand) -> int`  

Calculates how many bases of the comparand are contained by this Range.  

Another Range object  

Returns
-------
The number of bases which are contained (equivalent to the length of the
comparand), or 0 if it is not contained.  
";

%feature("docstring") sbol::Range::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Range::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

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
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Range::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Range::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Range::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Range::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Range::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Range::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Range::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Range::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Range::overlaps "
`overlaps(comparand) -> int`  

Calculates how many bases separate this Range from the comparand.  

Another Range object  

Returns
-------
The number of bases by which the Ranges overlap. If they overlap, this is always
a positive number regardless of direction. If they do not overlap, returns zero  
";

%feature("docstring") sbol::Range::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Range::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Range::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Range::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Range::~Range "
`~Range()`  
";

%feature("docstring") sbol::Range::Range "
`Range(uri=\"example\", start=1, end=2)`  

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
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Range::precedes "
`precedes(comparand) -> int`  

Calculates how many bases separate these Ranges  Another Range object.  

Returns
-------
The number of bases by which this Range precedes the comparand, or 0 if it does
not precede  
";

// File: classsbol_1_1_referenced_object.xml


%feature("docstring") sbol::ReferencedObject "

A reference to another SBOL object Contains a Uniform Resource Identifier (URI)
that refers to an an associated object.  

The object it points to may be another resource in this Document or an external
reference, for example to an object in an external repository or database. In
the SBOL specification, association by reference is indicated in class diagrams
by arrows with open (white) diamonds.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/object.h
";

%feature("docstring") sbol::ReferencedObject::end "
`end() -> iterator`  
";

%feature("docstring") sbol::ReferencedObject::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::ReferencedObject::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::ReferencedObject::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::ReferencedObject::add "
`add(uri)`  

Append a URI reference of an object to the property store.  

Parameters
----------
* `uri` :  
    The full URI of the referenced object, e.g., my_obj.identity.get()  
";

%feature("docstring") sbol::ReferencedObject::add "
`add(obj)`  

Append a URI reference of an object to the property store.  

Parameters
----------
* `The` :  
    referenced object  
";

%feature("docstring") sbol::ReferencedObject::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::ReferencedObject::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::ReferencedObject::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::ReferencedObject::create "
`create(uri) -> std::string`  

Creates a new SBOL object corresponding to the RDF type specified in the
Property definition.  

Creates another SBOL object derived from TopLevel and adds it to the Document.  

Parameters
----------
* `uri` :  
    A Uniform Resource Identifier (URI) for the new object, or a displayId if
    operating in SBOL-compliant mode (library default)  

Returns
-------
The full URI of the created object  

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

%feature("docstring") sbol::ReferencedObject::set "
`set(uri)`  

Set the property with a URI reference to an object.  

Parameters
----------
* `The` :  
    full URI of the referenced object, e.g., my_obj.identity.get()  
";

%feature("docstring") sbol::ReferencedObject::set "
`set(obj)`  

Set the property with a URI reference to an object, overwriting the first value
in the property store.  

Parameters
----------
* `The` :  
    referenced object  
";

%feature("docstring") sbol::ReferencedObject::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::ReferencedObject::set "
`set(new_value)`  
";

%feature("docstring") sbol::ReferencedObject::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::ReferencedObject::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::ReferencedObject::setReference "
`setReference(uri)`  
";

%feature("docstring") sbol::ReferencedObject::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::ReferencedObject::write "
`write()`  
";

%feature("docstring") sbol::ReferencedObject::size "
`size() -> int`  
";

%feature("docstring") sbol::ReferencedObject::getAll "
`getAll() -> std::vector< std::string >`  
";

%feature("docstring") sbol::ReferencedObject::get "
`get() -> std::string`  

Get first URI.  

Returns
-------
A string of characters used to identify a resource  
";

%feature("docstring") sbol::ReferencedObject::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::ReferencedObject::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::ReferencedObject::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::ReferencedObject::addReference "
`addReference(uri)`  
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
`ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound,
    upper_bound, validation_rules, initial_value)`  
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
`ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound,
    upper_bound, validation_rules)`  
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
`ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound,
    upper_bound, initial_value)`  
";

%feature("docstring") sbol::ReferencedObject::ReferencedObject "
`ReferencedObject(property_owner, type_uri, reference_type_uri, lower_bound,
    upper_bound)`  
";

// File: classsbol_1_1_sample_roster.xml


%feature("docstring") sbol::SampleRoster "

A SampleRoster is a container used to group Builds that are included in an
experiment together. A SampleRoster can be used to generate a Test in a Design-
Build-Test-Learn workflow.  

Attributes
----------
* `samples` : `ReferencedObject`  
    References to Builds which were tested in an experiment.  

* `members` : `URIProperty`  
    The members property of a Collection is OPTIONAL and MAY contain a set of
    URI references to zero or more TopLevel objects.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/dbtl.h
";

%feature("docstring") sbol::SampleRoster::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SampleRoster::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SampleRoster::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::SampleRoster::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SampleRoster::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SampleRoster::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SampleRoster::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SampleRoster::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SampleRoster::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SampleRoster::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SampleRoster::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SampleRoster::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SampleRoster::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SampleRoster::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::SampleRoster::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::SampleRoster::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::SampleRoster::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::SampleRoster::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::SampleRoster::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SampleRoster::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SampleRoster::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SampleRoster::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SampleRoster::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SampleRoster::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SampleRoster::SampleRoster "
`SampleRoster(uri=\"example\", version=VERSION_STRING)`  

Construct a new SampleRoster object.  

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

// File: classsbol_1_1_s_b_o_l_error.xml


%feature("docstring") sbol::SBOLError "
";

%feature("docstring") sbol::SBOLError::what "
`what() -> const char *`  
";

%feature("docstring") sbol::SBOLError::SBOLError "
`SBOLError(error_code, message)`  
";

%feature("docstring") sbol::SBOLError::error_code "
`error_code() -> SBOLErrorCode`  
";

// File: classsbol_1_1_s_b_o_l_object.xml


%feature("docstring") sbol::SBOLObject "

An SBOLObject converts a C++ class data structure into an RDF triple store and
contains methods for serializing and parsing RDF triples.  

Attributes
----------
* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/object.h
";

%feature("docstring") sbol::SBOLObject::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SBOLObject::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SBOLObject::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SBOLObject::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::SBOLObject::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SBOLObject::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SBOLObject::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

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
`SBOLObject(uri=\"example\")`  
";

%feature("docstring") sbol::SBOLObject::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SBOLObject::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SBOLObject::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SBOLObject::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SBOLObject::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SBOLObject::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SBOLObject::~SBOLObject "
`~SBOLObject()`  
";

%feature("docstring") sbol::SBOLObject::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SBOLObject::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SBOLObject::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SBOLObject::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SBOLObject::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

// File: classsbol_1_1_search_query.xml


%feature("docstring") sbol::SearchQuery "

A SearchQuery object is used to configure advanced searches for bioparts in a
PartShop. Advanced searches are useful for matching values across multiple
fields, or to specify multiple values in a single field.  

Attributes
----------
* `objectType` : `URIProperty`  
    Set this property to indicate the type of SBOL object to search for. Set to
    SBOL_COMPONENT_DEFINITION by default.  

* `limit` : `IntProperty`  
    Set this property to specify the total number of records to retrieve from a
    search request. By default 25 records are retrieved.  

* `offset` : `IntProperty`  
    When the number of search hits exceeds the limit, the offset property can be
    used to retrieve more records.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/partshop.h
";

%feature("docstring") sbol::SearchQuery::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SearchQuery::SearchQuery "
`SearchQuery(search_target=SBOL_COMPONENT_DEFINITION, offset=0, limit=25)`  

SearchQuery constructor.  

Parameters
----------
* `search_target` :  
    The type of SBOL object to search for, indicated using a URI. Set to
    SBOL_COMPONENT_DEFINITION by default.  
";

%feature("docstring") sbol::SearchQuery::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SearchQuery::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::SearchQuery::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SearchQuery::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SearchQuery::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::SearchQuery::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SearchQuery::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SearchQuery::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SearchQuery::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SearchQuery::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::SearchQuery::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SearchQuery::~SearchQuery "
`~SearchQuery()`  

Retrieve a child object by URI.  
";

%feature("docstring") sbol::SearchQuery::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SearchQuery::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SearchQuery::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SearchQuery::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SearchQuery::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SearchQuery::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SearchQuery::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SearchQuery::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SearchQuery::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SearchQuery::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::SearchQuery::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SearchQuery::compare "
`compare(comparand) -> int`  

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

// File: classsbol_1_1_search_response.xml


%feature("docstring") sbol::SearchResponse "

A SearchResponse is a container of search records returned by a search request.  

Attributes
----------
* `records` : `std::vector< sbol::Identified *>`  

* `python_iter` : `std::vector< Identified * >::iterator`  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/partshop.h
";

%feature("docstring") sbol::SearchResponse::end "
`end() -> iterator`  
";

%feature("docstring") sbol::SearchResponse::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SearchResponse::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SearchResponse::~SearchResponse "
`~SearchResponse()`  
";

%feature("docstring") sbol::SearchResponse::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::SearchResponse::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SearchResponse::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SearchResponse::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::SearchResponse::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SearchResponse::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::SearchResponse::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SearchResponse::size "
`size() -> int`  

Returns the number of records contained in a search response.  
";

%feature("docstring") sbol::SearchResponse::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SearchResponse::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::SearchResponse::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SearchResponse::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SearchResponse::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::SearchResponse::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::SearchResponse::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SearchResponse::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SearchResponse::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SearchResponse::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SearchResponse::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SearchResponse::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SearchResponse::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::SearchResponse::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SearchResponse::SearchResponse "
`SearchResponse()`  
";

%feature("docstring") sbol::SearchResponse::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SearchResponse::extend "
`extend(response)`  

Adds more search records to an existing SearchResponse.  

Parameters
----------
* `response` :  
    A SearchResponse object  
";

%feature("docstring") sbol::SearchResponse::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

// File: classsbol_1_1_sequence.xml


%feature("docstring") sbol::Sequence "

The primary structure (eg, nucleotide or amino acid sequence) of a
ComponentDefinition object.  

Attributes
----------
* `elements` : `TextProperty`  
    The elements property is a REQUIRED String of characters that represents the
    constituents of a biological or chemical molecule. For example, these
    characters could represent the nucleotide bases of a molecule of DNA, the
    amino acid residues of a protein, or the atoms and chemical bonds of a small
    molecule.  

* `encoding` : `URIProperty`  
    The encoding property is REQUIRED and has a data type of URI.  

    This property MUST indicate how the elements property of a Sequence MUST be
    formed and interpreted. For example, the elements property of a Sequence
    with an IUPAC DNA encoding property MUST contain characters that represent
    nucleotide bases, such as a, t, c, and g. The elements property of a
    Sequence with a Simplified Molecular-Input Line-Entry System (SMILES)
    encoding, on the other hand, MUST contain characters that represent atoms
    and chemical bonds, such as C, N, O, and =. It is RECOMMENDED that the
    encoding property contains a URI from the table below. The terms in the
    table are organized by the type of ComponentDefinition that typically refer
    to a Sequence with such an encoding. When the encoding of a Sequence is well
    described by one of the URIs in the table, it MUST contain that URI.
    ComponentDefinition type  

    Encoding  

    libSBOL Symbol  

    URI  

    DNA, RNA  

    IUPAC DNA, RNA  

    SBOL_ENCODING_IUPAC  

    http://www.chem.qmul.ac.uk/iubmb/misc/naseq.html  

    Protein  

    IUPAC Protein  

    SBOL_ENCODING_IUPAC_PROTEIN  

    http://www.chem.qmul.ac.uk/iupac/AminoAcid/  

    Small Molecule  

    SMILES  

    SBOL_ENCODING_SMILES  

    http://www.opensmiles.org/opensmiles.html  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/sequence.h
";

%feature("docstring") sbol::Sequence::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Sequence::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Sequence::assemble "
`assemble(composite_sequence=\"\") -> std::string`  

Calculates the complete sequence of a high-level Component from the sequence of
its subcomponents.  

Pior to assembling the the complete sequence, you must assemble a template
design by calling ComponentDefinition::assemble for the ComponentDefinition that
references this Sequence.  

Parameters
----------
* `composite_sequence` :  
    Typically no value for the composite sequence should be specified by the
    user. This parameter is used to hold the composite sequence as it is passed
    to function calls at a higher-level of the recursion stack.  
";

%feature("docstring") sbol::Sequence::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Sequence::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Sequence::synthesize "
`synthesize(clone_id) -> ComponentDefinition &`  

Parameters
----------
* `clone_id` :  
    A URI for the build, or displayId if working in SBOLCompliant mode.  
";

%feature("docstring") sbol::Sequence::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Sequence::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Sequence::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Sequence::~Sequence "
`~Sequence()`  
";

%feature("docstring") sbol::Sequence::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Sequence::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Sequence::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Sequence::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Sequence::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Sequence::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Sequence::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Sequence::Sequence "
`Sequence(uri=\"example\", elements=\"\", encoding=SBOL_ENCODING_IUPAC,
    version=VERSION_STRING)`  

Construct a Seqiemce.  

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

%feature("docstring") sbol::Sequence::Sequence "
`Sequence(type_uri, uri, elements, encoding, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `type_uri` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Sequence::compile "
`compile() -> std::string`  

Synonomous with Sequence::assemble. Calculates the complete sequence of a high-
level Component from the sequence of its subcomponents. Prior to assembling the
the complete sequence, you must assemble a template design by calling
ComponentDefinition::assemble for the ComponentDefinition that references this
Sequence.  
";

%feature("docstring") sbol::Sequence::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Sequence::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Sequence::length "
`length() -> int`  

Returns
-------
The length of the primary sequence in the elements property  
";

%feature("docstring") sbol::Sequence::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Sequence::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Sequence::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Sequence::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Sequence::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Sequence::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Sequence::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Sequence::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

// File: classsbol_1_1_sequence_annotation.xml


%feature("docstring") sbol::SequenceAnnotation "

The SequenceAnnotation class describes one or more regions of interest on the
Sequence objects referred to by its parent ComponentDefinition. In addition,
SequenceAnnotation objects can describe the substructure of their parent
ComponentDefinition through association with the Component objects contained by
this ComponentDefinition.  

Attributes
----------
* `component` : `ReferencedObject`  
    The component property is OPTIONAL and has a data type of URI. This URI MUST
    refer to a Component that is contained by the same parent
    ComponentDefinition that contains the SequenceAnnotation. In this way, the
    properties of the SequenceAnnotation, such as its description and locations,
    are associated with part of the substructure of its parent
    ComponentDefinition.  

* `locations` : `OwnedObject< Location >`  
    The locations property is a REQUIRED set of one or more Location objects
    that indicate which elements of a Sequence are described by the
    SequenceAnnotation.  

    Allowing multiple Location objects on a single SequenceAnnotation is
    intended to enable representation of discontinuous regions (for example, a
    Component encoded across a set of exons with interspersed introns). As such,
    the Location objects of a single SequenceAnnotation SHOULD NOT specify
    overlapping regions, since it is not clear what this would mean. There is no
    such concern with different SequenceAnnotation objects, however, which can
    freely overlap in Location (for example, specifying overlapping linkers for
    sequence assembly).  

* `roles` : `URIProperty`  
    Alternatively to describing substructure, a SequenceAnnotation can be
    utilized to identify a feature, such as a GenBank feature, of a specified
    Sequence.  

    In this use case, the SequenceAnnotation MUST NOT have a component property,
    but instead it would have a roles property. The roles property comprises an
    OPTIONAL set of zero or more URIs describing the specified sequence feature
    being annotated. If provided, these role URIs MUST identify terms from
    appropriate ontologies. Roles are not restricted to describing biological
    function; they may annotate Sequences function in any domain for which an
    ontology exists. It is RECOMMENDED that these role URIs identify terms that
    are compatible with the type properties of this SequenceAnnotations parent
    ComponentDefinition. For example, a role of a SequenceAnnotation which
    belongs to a ComponentDefinition of type DNA might refer to terms from the
    Sequence Ontology. See documentation for ComponentDefinition for a table of
    recommended ontology terms.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/sequenceannotation.h
";

%feature("docstring") sbol::SequenceAnnotation::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceAnnotation::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SequenceAnnotation::length "
`length() -> int`  

The length of a SequenceAnnotation in base coordinates.  
";

%feature("docstring") sbol::SequenceAnnotation::precedes "
`precedes(comparand) -> bool`  

Tests if the comparand SequenceAnnotation precedes this one according to base
coordinates.  

Parameters
----------
* `comparand` :  
    Another SequenceAnnotation  

Returns
-------
true or false  
";

%feature("docstring") sbol::SequenceAnnotation::precedes "
`precedes(comparand_list) -> std::vector< SequenceAnnotation * >`  
";

%feature("docstring") sbol::SequenceAnnotation::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SequenceAnnotation::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceAnnotation::follows "
`follows(comparand) -> bool`  

Tests if the comparand SequenceAnnotation follows this one according to base
coordinates.  

Parameters
----------
* `comparand` :  
    Another SequenceAnnotation  

Returns
-------
true or false  
";

%feature("docstring") sbol::SequenceAnnotation::follows "
`follows(comparand_list) -> std::vector< SequenceAnnotation * >`  
";

%feature("docstring") sbol::SequenceAnnotation::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceAnnotation::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SequenceAnnotation::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceAnnotation::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SequenceAnnotation::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::SequenceAnnotation::extract "
`extract(start_reference=1) -> ComponentDefinition &`  

Convert a SequenceAnnotation to a subcomponent.  

Returns
-------
A ComponentDefinition representing the subcomponent  
";

%feature("docstring") sbol::SequenceAnnotation::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SequenceAnnotation::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceAnnotation::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SequenceAnnotation::contains "
`contains(comparand) -> bool`  

Tests if the comparand SequenceAnnotation is contained within the same start and
end base coordinates as this one.  

This is mutually exclusive with overlaps.  

Parameters
----------
* `comparand` :  
    Another SequenceAnnotation  

Returns
-------
true or false  
";

%feature("docstring") sbol::SequenceAnnotation::contains "
`contains(comparand_list) -> std::vector< SequenceAnnotation * >`  
";

%feature("docstring") sbol::SequenceAnnotation::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SequenceAnnotation::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SequenceAnnotation::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceAnnotation::overlaps "
`overlaps(comparand) -> bool`  

Tests if the comparand SequenceAnnotation overlaps with this one in the primary
sequence.  

Parameters
----------
* `comparand` :  
    Another SequenceAnnotation  

Returns
-------
true or false  
";

%feature("docstring") sbol::SequenceAnnotation::overlaps "
`overlaps(comparand_list) -> std::vector< SequenceAnnotation * >`  
";

%feature("docstring") sbol::SequenceAnnotation::~SequenceAnnotation "
`~SequenceAnnotation()`  
";

%feature("docstring") sbol::SequenceAnnotation::SequenceAnnotation "
`SequenceAnnotation(uri=\"example\", version=VERSION_STRING)`  

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
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SequenceAnnotation::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceAnnotation::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceAnnotation::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SequenceAnnotation::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

// File: classsbol_1_1_sequence_constraint.xml


%feature("docstring") sbol::SequenceConstraint "

The SequenceConstraint class can be used to assert restrictions on the relative,
sequence-based positions of pairs of Component objects contained by the same
parent ComponentDefinition. The primary purpose of this class is to enable the
specification of partially designed ComponentDefinition objects, for which the
precise positions or orientations of their contained Component objects are not
yet fully determined.  

Attributes
----------
* `subject` : `ReferencedObject`  
    The subject property is REQUIRED and MUST contain a URI that refers to a
    Component contained by the same parent ComponentDefinition that contains the
    SequenceConstraint.  

* `object` : `ReferencedObject`  
    The object property is REQUIRED and MUST contain a URI that refers to a
    Component contained by the same parent ComponentDefinition that contains the
    SequenceConstraint. This Component MUST NOT be the same Component that the
    SequenceConstraint refers to via its subject property.  

* `restriction` : `URIProperty`  
    The restriction property is REQUIRED and has a data type of URI.  

    This property MUST indicate the type of structural restriction on the
    relative, sequence-based positions or orientations of the subject and object
    Component objects. The URI value of this property SHOULD come from the
    RECOMMENDED URIs in the following table.
    libSBOL Symbol  

    Description  

    SBOL_RESTRICTION_PRECEDES  

    The position of the subject Component MUST precede that of the object
    Component.  
     If each one is associated with a SequenceAnnotation, then the
    SequenceAnnotation  
    associated with the subject Component MUST specify a region that starts
    before  
    the region specified by the SequenceAnnotation associated with the object
    Component.  

    SBOL_RESTRICTION_SAME_ORIENTATION_AS  

    The subject and object Component objects MUST have the same orientation. If
    each  
    one is associated with a SequenceAnnotation, then the orientation URIs of
    the  Location objects of the first SequenceAnnotation MUST be among those of
    the  
    second SequenceAnnotation, and vice versa.  

    SBOL_RESTRICTION_OPPOSITE_ORIENTATION_AS  

    The subject and object Component objects MUST have opposite orientations. If  
    each one is associated with a SequenceAnnotation, then the orientation URIs
    of  
    the Location objects of one SequenceAnnotation MUST NOT be among those of
    the  
    other SequenceAnnotation.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/sequenceconstraint.h
";

%feature("docstring") sbol::SequenceConstraint::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SequenceConstraint::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SequenceConstraint::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SequenceConstraint::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceConstraint::find_property "
`find_property(uri) -> SBOLObject *`  

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
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceConstraint::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceConstraint::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SequenceConstraint::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SequenceConstraint::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceConstraint::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SequenceConstraint::compare "
`compare(comparand) -> int`  

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
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SequenceConstraint::~SequenceConstraint "
`~SequenceConstraint()`  
";

%feature("docstring") sbol::SequenceConstraint::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SequenceConstraint::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceConstraint::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SequenceConstraint::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SequenceConstraint::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SequenceConstraint::SequenceConstraint "
`SequenceConstraint(uri=\"example\", subject=\"\", object=\"\",
    restriction=SBOL_RESTRICTION_PRECEDES, version=VERSION_STRING)`  

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

%feature("docstring") sbol::SequenceConstraint::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SequenceConstraint::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

// File: classsbol_1_1_small_molecule_activation_interaction.xml


%feature("docstring") sbol::SmallMoleculeActivationInteraction "

Attributes
----------
* `ligand` : `AliasedProperty< FunctionalComponent >`  

* `transcriptionFactor` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SmallMoleculeActivationInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::SmallMoleculeActivationInteraction "
`SmallMoleculeActivationInteraction(uri, ligand, transcription_factor)`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SmallMoleculeActivationInteraction::compare "
`compare(comparand) -> int`  

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

// File: classsbol_1_1_small_molecule_inhibition_interaction.xml


%feature("docstring") sbol::SmallMoleculeInhibitionInteraction "

Attributes
----------
* `ligand` : `AliasedProperty< FunctionalComponent >`  

* `transcriptionFactor` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::SmallMoleculeInhibitionInteraction "
`SmallMoleculeInhibitionInteraction(uri, ligand, transcription_factor)`  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::SmallMoleculeInhibitionInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

// File: classsbol_1_1_test.xml


%feature("docstring") sbol::Test "

A Test is a container for experimental data. A Test is the product of the third
step of libSBOL's formalized Design-Build-Test-Analyze workflow.  

Attributes
----------
* `samples` : `ReferencedObject`  
    References to Builds which were tested in the experiment.  

* `dataFiles` : `ReferencedObject`  
    References to file Attachments which contain experimental data sets.  

* `members` : `URIProperty`  
    The members property of a Collection is OPTIONAL and MAY contain a set of
    URI references to zero or more TopLevel objects.  

* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/dbtl.h
";

%feature("docstring") sbol::Test::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Test::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Test::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Test::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::Test::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Test::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Test::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::Test::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Test::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Test::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::Test::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Test::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Test::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::Test::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Test::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::Test::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Test::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Test::~Test "
`~Test()`  
";

%feature("docstring") sbol::Test::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Test::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Test::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Test::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Test::Test "
`Test(uri=\"example\", version=VERSION_STRING)`  

Construct a new Test object.  

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

%feature("docstring") sbol::Test::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::Test::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::Test::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Test::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

// File: classsbol_1_1_text_property.xml


%feature("docstring") sbol::TextProperty "

TextProperty objects are used to contain string literals.  

They can be used as member objects inside custom SBOL Extension classes.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::TextProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::TextProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::TextProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::TextProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::TextProperty::get "
`get() -> std::string`  

Basic getter for all SBOL literal properties.  

Returns
-------
A string literal  
";

%feature("docstring") sbol::TextProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::TextProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::TextProperty::getAll "
`getAll() -> std::vector< std::string >`  
";

%feature("docstring") sbol::TextProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::TextProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::TextProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::TextProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::TextProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::TextProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::TextProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::TextProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::TextProperty::write "
`write()`  
";

%feature("docstring") sbol::TextProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::TextProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::TextProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::TextProperty::TextProperty "
`TextProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules, initial_value)`  

Initialize the TextProperty with a value.  

Validation rules are checked upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::TextProperty::TextProperty "
`TextProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules)`  

Initialize a TextProperty without a value.  

No validation rules are run upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::TextProperty::TextProperty "
`TextProperty(property_owner, type_uri, lower_bound, upper_bound,
    initial_value)`  
";

%feature("docstring") sbol::TextProperty::TextProperty "
`TextProperty(property_owner, type_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::TextProperty::getUpperBound "
`getUpperBound() -> char`  
";

// File: classsbol_1_1_top_level.xml


%feature("docstring") sbol::TopLevel "

All SBOL classes derived from TopLevel appear as top level nodes in the RDF/XML
document tree and SBOL files. An abstract class.  

Attributes
----------
* `attachments` : `ReferencedObject`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/toplevel.h
";

%feature("docstring") sbol::TopLevel::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TopLevel::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::TopLevel::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::TopLevel::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::TopLevel::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TopLevel::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::TopLevel::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::TopLevel::TopLevel "
`TopLevel(type_uri=SBOL_TOP_LEVEL, uri=\"example\", version=VERSION_STRING)`  
";

%feature("docstring") sbol::TopLevel::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TopLevel::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::TopLevel::~TopLevel "
`~TopLevel()`  
";

%feature("docstring") sbol::TopLevel::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TopLevel::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages={}) -> SBOLClass &`  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `The` :  
    type of SBOL object to generate  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Design &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Design &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Build &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Build &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Test &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Test &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri) -> Analysis &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> Analysis &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate(uri, agent, plan, usages) -> SBOLClass &`  
";

%feature("docstring") sbol::TopLevel::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::TopLevel::simpleCopy "
`simpleCopy(uri) -> SBOLClass &`  

Copies an object.  

No child objects are copied.  

Parameters
----------
* `uri` :  
    A URI for the new object, or a displayId if operating in SBOLCompliant mode  

templateparam
-------------
* `Usually` :  
    the same type of SBOL object as this  
";

%feature("docstring") sbol::TopLevel::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TopLevel::addToDocument "
`addToDocument(arg1)`  
";

%feature("docstring") sbol::TopLevel::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TopLevel::initialize "
`initialize(uri)`  
";

%feature("docstring") sbol::TopLevel::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::TopLevel::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::TopLevel::copy "
`copy(target_doc=NULL, ns=\"\", version=\"\") -> SBOLClass &`  

Recursively copies an object.  

Use this to copy an object to a new document, a new namespace, or to increment
its version recursively. An object be recursively copied into a new document and
a new namespace, assuming compliant URIs. If the optional version argument is
specified, it will be used instead of incrementing the copied object's version
(this can be used when using a custom versioning scheme other than libSBOL's
default).  

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
    by setHomespace) in all SBOL-compliant URIs.  
* `version` :  
    A new version  

Returns
-------
The copied object.  
";

%feature("docstring") sbol::TopLevel::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::TopLevel::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::TopLevel::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::TopLevel::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

// File: classsbol_1_1_transcriptional_activation_interaction.xml


%feature("docstring") sbol::TranscriptionalActivationInteraction "

Attributes
----------
* `activator` : `AliasedProperty< FunctionalComponent >`  

* `targetPromoter` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::TranscriptionalActivationInteraction::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::TranscriptionalActivationInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::TranscriptionalActivationInteraction "
`TranscriptionalActivationInteraction(uri, activator, target_promoter)`  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TranscriptionalActivationInteraction::update_uri "
`update_uri()`  
";

// File: classsbol_1_1_transcriptional_repression_interaction.xml


%feature("docstring") sbol::TranscriptionalRepressionInteraction "

Attributes
----------
* `repressor` : `AliasedProperty< FunctionalComponent >`  

* `targetPromoter` : `AliasedProperty< FunctionalComponent >`  

* `types` : `URIProperty`  
    The types property is a REQUIRED set of URIs that describes the behavior
    represented by an Interaction.  

    The types property MUST contain one or more URIs that MUST identify terms
    from appropriate ontologies. It is RECOMMENDED that at least one of the URIs
    contained by the types property refer to a term from the occurring entity
    branch of the Systems Biology Ontology (SBO). (See
    http://www.ebi.ac.uk/sbo/main/) The following table provides a list of
    possible SBO terms for the types property and their corresponding URIs.
    Type  

    URI for SBO Term  

    LibSBOL symbol  

    Biochemical Reaction  

    http://identifiers.org/biomodels.sbo/SBO:0000176  

    SBO_BIOCHEMICAL_REACTION  

    Inhibition  

    http://identifiers.org/biomodels.sbo/SBO:0000169  

    SBO_INHIBITION  

    Stimulation  

    http://identifiers.org/biomodels.sbo/SBO:0000170  

    SBO_STIMULATION  

    Genetic Production  

    http://identifiers.org/biomodels.sbo/SBO:0000589  

    SBO_GENETIC_PRODUCTION  

    Non-Covalent Binding  

    http://identifiers.org/biomodels.sbo/SBO:0000177  

    SBO_NONCOVALENT_BINDING  

    Degradation  

    http://identifiers.org/biomodels.sbo/SBO:0000179  

    SBO_DEGRADATION  

    Control  

    http://identifiers.org/biomodels.sbo/SBO:0000168  

    SBO_CONTROL  

* `participations` : `OwnedObject< Participation >`  
    The participations property is an OPTIONAL and MAY contain a set of
    Participation objects, each of which identifies the roles that its
    referenced FunctionalComponent plays in the Interaction. Even though an
    Interaction generally contains at least one Participation, the case of zero
    Participation objects is allowed because it is plausible that a designer
    might want to specify that an Interaction will exist, even if its
    participants have not yet been determined.  

* `functionalComponents` : `OwnedObject< FunctionalComponent >`  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::TranscriptionalRepressionInteraction::TranscriptionalRepressionInteraction "
`TranscriptionalRepressionInteraction(uri, repressor, target_promoter)`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::TranscriptionalRepressionInteraction::compare "
`compare(comparand) -> int`  

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

// File: classsbol_1_1_u_r_i_property.xml


%feature("docstring") sbol::URIProperty "

A URIProperty may contain a restricted type of string that conforms to the
specification for a Uniform Resource Identifier (URI), typically consisting of a
namespace authority followed by an identifier.  

A URIProperty often contains a reference to an SBOL object or may contain an
ontology term.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::URIProperty::write "
`write()`  
";

%feature("docstring") sbol::URIProperty::URIProperty "
`URIProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules, initial_value)`  

Initialize the property with a value that is passed through a constructor for
the parent SBOLObject.  

Validation rules are checked upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::URIProperty::URIProperty "
`URIProperty(property_owner, type_uri, lower_bound, upper_bound,
    validation_rules)`  

Initialize a Property without a value.  

No validation rules are run upon initialization.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
* `validation_rules` :  
    A vector of pointers to the validation functions  
";

%feature("docstring") sbol::URIProperty::URIProperty "
`URIProperty(property_owner, type_uri, lower_bound, upper_bound, initial_value)`  
";

%feature("docstring") sbol::URIProperty::URIProperty "
`URIProperty(property_owner, type_uri, lower_bound, upper_bound)`  
";

%feature("docstring") sbol::URIProperty::getAll "
`getAll() -> std::vector< std::string >`  
";

%feature("docstring") sbol::URIProperty::get "
`get() -> std::string`  

Get first URI.  

Returns
-------
A string of characters used to identify a resource  
";

%feature("docstring") sbol::URIProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::URIProperty::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::URIProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::URIProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::URIProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::URIProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::URIProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::URIProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::URIProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::URIProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::URIProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

%feature("docstring") sbol::URIProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::URIProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::URIProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::URIProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::URIProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::URIProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::URIProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

// File: classsbol_1_1_usage.xml


%feature("docstring") sbol::Usage "

How different entities are used in an Activity is specified with the Usage
class, which is linked from an Activity through the qualifiedUsage relationship.
A Usage is then linked to an Entity through the Entitys URI and the role of
this entity is qualified with the hadRole property. When the wasDerivedFrom
property is used together with the full provenance described here, the entity
pointed at by the wasDerivedFrom property MUST be included in a Usage.  

Attributes
----------
* `entity` : `URIProperty`  
    The entity property is REQUIRED and MUST contain a URI which MAY refer to an
    SBOL Identified object.  

* `roles` : `URIProperty`  
    The hadRole property is REQUIRED and MAY contain a URI that refers to a
    particular term describing the usage of an entity referenced by the entity
    property.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/provo.h
";

%feature("docstring") sbol::Usage::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Usage::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::Usage::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::Usage::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Usage::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::Usage::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::Usage::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Usage::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::Usage::~Usage "
`~Usage()`  
";

%feature("docstring") sbol::Usage::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::Usage::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::Usage::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Usage::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::Usage::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

%feature("docstring") sbol::Usage::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::Usage::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::Usage::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::Usage::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::Usage::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::Usage::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::Usage::Usage "
`Usage(uri=\"example\", entity=\"\", role=\"\", version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
";

%feature("docstring") sbol::Usage::Usage "
`Usage(type, uri, entity, role, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::Usage::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

// File: classsbol_1_1_variable_component.xml


%feature("docstring") sbol::VariableComponent "

The VariableComponent class can be used to specify a choice of
ComponentDefinition objects for any new Component derived from a template
Component in the template ComponentDefinition. This specification is made using
the class properties variable, variants, variantCollections, and
variantDerivations. While the variants, variantCollections, and
variantDerivations properties are OPTIONAL, at least one of them MUST NOT be
empty.  

Attributes
----------
* `variable` : `ReferencedObject`  
    The variable property is REQUIRED and MUST contain a URI that refers to a
    template `Component` in the template `ComponentDefinition`. If the
    wasDerivedFrom property of a Component refers to this template Component,
    then the definition property of the derived Component MUST refer to one of
    the ComponentDefinition objects referred to by the variants property of the
    VariableComponent. If not, then this definition property MUST either (1)
    refer to one of the ComponentDefinition objects from a Collection referred
    to by the variantCollections property of the VariableComponent, or (2) refer
    to a ComponentDefinition derived from a CombinatorialDerivation referred to
    by the variantDerivations property of the VariableComponent.  

* `repeat` : `URIProperty`  
    The `repeat` property is REQUIRED and has a data type of URI.  

    This property specifies how many `Component` objects can be derived from the
    template `Component` during the derivation of a new `ComponentDefinition`.
    The URI value of this property MUST come from the REQUIRED `operator` URIs
    provided in the table below
    Operator URI  

    Description  

    http://sbols.org/v2#zeroOrOne  

    No more than one `Component` in the derived `ComponentDefinition` SHOULD
    have a `wasDerivedFrom` property that refers to the template `Component`.  

    http://sbols.org/v2#one  

    Exactly one `Component` in the derived `ComponentDefinition` SHOULD have a
    `wasDerivedFrom` property that refers to the template `Component`.  

    http://sbols.org/v2#zeroOrMore  

    Any number of `Component` objects in the derived `ComponentDefinition` MAY
    have `wasDerivedFrom` properties that refer to the template `Component`.  

    http://sbols.org/v2#oneOrMore  

    At least one `Component` in the derived `ComponentDefinition` SHOULD have a
    `wasDerivedFrom` property that refers to the template `Component`.  

* `variants` : `ReferencedObject`  
    The variants property is OPTIONAL and MAY contain zero or more URIs that
    each refer to a ComponentDefinition. This property specifies individual
    ComponentDefinition objects to serve as options when deriving a new
    Component from the template Component.  

* `variantCollections` : `ReferencedObject`  
    The variantCollections property is OPTIONAL and MAY contain zero or more
    URIs that each refer to a Collection. The members property of each
    Collection referred to in this way MUST NOT be empty and MUST refer only to
    ComponentDefinition objects. This property enables the convenient
    specification of existing groups of ComponentDefinition objects to serve as
    options when deriving a new Component from the template Component.  

* `variantDerivations` : `ReferencedObject`  
    The variantDerivations property is OPTIONAL and MAY contain zero or more
    URIs that each refer to a CombinatorialDerivation. This property enables the
    convenient specification of ComponentDefinition objects derived in
    accordance with another CombinatorialDerivation to serve as options when
    deriving a new Component from the template Component. The variantDerivations
    property of a VariableComponent MUST NOT refer to the
    CombinatorialDerivation that contains this VariableComponent (no cyclic
    derivations are allowed.  

* `persistentIdentity` : `URIProperty`  
    The persistentIdentity property is OPTIONAL and has a data type of URI. This
    URI serves to uniquely refer to a set of SBOL objects that are different
    versions of each other. An Identified object MUST be referred to using
    either its identity URI or its persistentIdentity URI.  

* `displayId` : `TextProperty`  
    The displayId property is an OPTIONAL identifier with a data type of String.
    This property is intended to be an intermediate between name and identity
    that is machine-readable, but more human-readable than the full URI of an
    identity. If the displayId property is used, then its String value SHOULD be
    locally unique (global uniqueness is not necessary) and MUST be composed of
    only alphanumeric or underscore characters and MUST NOT begin with a digit.  

* `version` : `VersionProperty`  
    If the version property is used, then it is RECOMMENDED that version
    numbering follow the conventions of semantic versioning, particularly as
    implemented by Maven. This convention represents versions as sequences of
    numbers and qualifiers that are separated by the characters . and - and
    are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta).
    For a full explanation, see the linked resources.  

* `wasDerivedFrom` : `URIProperty`  
    The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL
    object with this property refers to another SBOL object or non-SBOL resource
    from which this object was derived. If the wasDerivedFrom property of an
    SBOL object A that refers to an SBOL object B has an identical
    persistentIdentity, and both A and B have a version, then the version of B
    MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself
    via its own wasDerivedFrom property or form a cyclical chain of references
    via its wasDerivedFrom property and those of other SBOL objects. For
    example, the reference chain  A was derived from B and B was derived from
    A is cyclical.  

* `wasGeneratedBy` : `ReferencedObject`  
    An Activity which generated this ComponentDefinition, eg., a design process
    like codon-optimization or a construction process like Gibson Assembly.  

* `name` : `TextProperty`  
    The name property is OPTIONAL and has a data type of String. This property
    is intended to be displayed to a human when visualizing an Identified
    object. If an Identified object lacks a name, then software tools SHOULD
    instead display the objects displayId or identity. It is RECOMMENDED that
    software tools give users the ability to switch perspectives between name
    properties that are human-readable and displayId properties that are less
    human-readable, but are more likely to be unique.  

* `description` : `TextProperty`  
    The description property is OPTIONAL and has a data type of String. This
    property is intended to contain a more thorough text description of an
    Identified object.  

* `identity` : `URIProperty`  
    The identity property is REQUIRED by all Identified objects and has a data
    type of URI. A given Identified objects identity URI MUST be globally
    unique among all other identity URIs. The identity of a compliant SBOL
    object MUST begin with a URI prefix that maps to a domain over which the
    user has control. Namely, the user can guarantee uniqueness of identities
    within this domain. For other best practices regarding URIs see Section 11.2
    of the SBOL specification doucment.  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/combinatorialderivation.h
";

%feature("docstring") sbol::VariableComponent::getAnnotation "
`getAnnotation(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Synonymous with getPropertyValue  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::VariableComponent::compare "
`compare(comparand) -> int`  

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

%feature("docstring") sbol::VariableComponent::getTypeURI "
`getTypeURI() -> rdf_type`  

Returns
-------
The uniform resource identifier that describes the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::VariableComponent::close "
`close()`  

Use this method to destroy an SBOL object that is not contained by a parent
Document.  

If the object does have a parent Document, instead use doc.close() with the
object's URI identity as an argument.  Recurse through child objects and delete
them.  
";

%feature("docstring") sbol::VariableComponent::setPropertyValue "
`setPropertyValue(property_uri, val)`  

Set and overwrite the value for a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::VariableComponent::find "
`find(uri) -> SBOLObject *`  

Search this object recursively to see if an object or any child object with URI
already exists.  

Parameters
----------
* `uri` :  
    The URI to search for.  

Returns
-------
A pointer to theobject with this URI if it exists, NULL otherwise  
";

%feature("docstring") sbol::VariableComponent::find_property "
`find_property(uri) -> SBOLObject *`  

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

%feature("docstring") sbol::VariableComponent::getPropertyValues "
`getPropertyValues(property_uri) -> std::vector< std::string >`  

Get all values of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
A vector of property values or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::VariableComponent::cast "
`cast() -> SBOLClass &`  
";

%feature("docstring") sbol::VariableComponent::apply "
`apply(callback_fn, user_data)`  
";

%feature("docstring") sbol::VariableComponent::find_reference "
`find_reference(uri) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    A URI, either an ontology term or an object reference, to search for  

Returns
-------
A vector containing all objects found that contain the URI in a property value  
";

%feature("docstring") sbol::VariableComponent::find_property_value "
`find_property_value(uri, value, matches={}) -> std::vector< SBOLObject * >`  

Search this object recursively to see if it contains a member property with the
given RDF type and indicated property value.  

Parameters
----------
* `uri` :  
    The RDF type of the property to search for.  
* `value` :  
    The property value to match  

Returns
-------
A vector containing all objects found that contain a member property with the
specified RDF type  
";

%feature("docstring") sbol::VariableComponent::getProperties "
`getProperties() -> std::vector< std::string >`  

Gets URIs for all properties contained by this object.  

This includes SBOL core properties as well as custom annotations. Use this to
find custom extension data in an SBOL file.  

Returns
-------
A vector of URIs that identify the properties contained in this object  
";

%feature("docstring") sbol::VariableComponent::addPropertyValue "
`addPropertyValue(property_uri, val)`  

Append a value to a user-defined annotation property.  

Either a literal or URI value  
";

%feature("docstring") sbol::VariableComponent::copy "
`copy(ns=\"\", version=\"\") -> SBOLClass &`  
";

%feature("docstring") sbol::VariableComponent::VariableComponent "
`VariableComponent(uri=\"example\", repeat=\"http://sbols.org/v2#one\",
    version=VERSION_STRING)`  

Constructor.  

Parameters
----------
* `uri` :  
    A full URI including a scheme, namespace, and identifier. If SBOLCompliance
    configuration is enabled, then this argument is simply the displayId for the
    new object and a full URI will automatically be constructed.  
* `repeat` :  
    A URI indicating how many `Component` objects can be derived from the
    template `Component`  
";

%feature("docstring") sbol::VariableComponent::VariableComponent "
`VariableComponent(type, uri, repeat, version)`  

Constructor used for defining extension classes.  

Parameters
----------
* `rdf_type` :  
    The RDF type for an extension class derived from this one  
";

%feature("docstring") sbol::VariableComponent::getClassName "
`getClassName(type) -> std::string`  

Returns
-------
Parses a local class name from the RDF-type of this SBOL Object  
";

%feature("docstring") sbol::VariableComponent::getPropertyValue "
`getPropertyValue(property_uri) -> std::string`  

Get the value of a custom annotation property by its URI.  

Parameters
----------
* `property_uri` :  
    The URI for the property  

Returns
-------
The value of the property or SBOL_ERROR_NOT_FOUND  
";

%feature("docstring") sbol::VariableComponent::update_uri "
`update_uri()`  
";

%feature("docstring") sbol::VariableComponent::generate "
`generate() -> SBOLClass &`  
";

%feature("docstring") sbol::VariableComponent::setAnnotation "
`setAnnotation(property_uri, val)`  

Set the value for a user-defined annotation property.  

Synonymous with setPropertyValue  If the value is a URI, it should be surrounded
by angle brackets, else it will be interpreted as a literal value  
";

// File: classsbol_1_1_version_property.xml


%feature("docstring") sbol::VersionProperty "

Contains a version number for an SBOL object.  

The VersionProperty follows Maven versioning semantics and includes a major,
minor, and patch version number.  

Attributes
----------
* `python_iter` : `std::vector< std::string >::iterator`  

C++ includes: /Users/bbartley/Dev/git/libSBOL/source/properties.h
";

%feature("docstring") sbol::VersionProperty::clear "
`clear()`  

Clear all property values.  
";

%feature("docstring") sbol::VersionProperty::getAll "
`getAll() -> std::vector< std::string >`  
";

%feature("docstring") sbol::VersionProperty::end "
`end() -> iterator`  
";

%feature("docstring") sbol::VersionProperty::major "
`major() -> int`  

Get major version.  

Returns
-------
The major version as an integer Splits the version string by a delimiter and
returns the major version number  
";

%feature("docstring") sbol::VersionProperty::set "
`set(new_value)`  

Basic setter for SBOL TextProperty and URIProperty.  

Parameters
----------
* `new_value` :  
    A new string value for the Property.  
";

%feature("docstring") sbol::VersionProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::VersionProperty::set "
`set(new_value)`  
";

%feature("docstring") sbol::VersionProperty::set "
`set(new_value)`  

Basic setter for SBOL IntProperty, but can be used with TextProperty as well.  

Parameters
----------
* `new_value` :  
    A new integer value for the property, which is converted to a raw string
    during serialization.  
";

%feature("docstring") sbol::VersionProperty::getLowerBound "
`getLowerBound() -> char`  
";

%feature("docstring") sbol::VersionProperty::getTypeURI "
`getTypeURI() -> rdf_type`  
";

%feature("docstring") sbol::VersionProperty::minor "
`minor() -> int`  

Get minor version.  

Returns
-------
The minor version as an integer Splits the version string by a delimiter and
returns the minor version number  
";

%feature("docstring") sbol::VersionProperty::copy "
`copy(target_property)`  

Copy property values to a target object's property fields.  
";

%feature("docstring") sbol::VersionProperty::VersionProperty "
`VersionProperty(property_owner, type_uri, lower_bound, upper_bound,
    initial_value)`  

Initialize the VersionProperty with a version string.  

If a version is specified, it will be checked to confirm it follows Maven
versioning semantics.  

Parameters
----------
* `type_uri` :  
    An RDF type for the property which determines how the property is serialized
    in SBOL files  
* `lower_bound` :  
    A char flag (typically '0' or '1') indicating the minimum number of values
    allowed for this property  
* `upper_bound` :  
    A char flag (typically '1' or '*') indicating the maximum number of values
    allowed for this property  
";

%feature("docstring") sbol::VersionProperty::decrementMajor "
`decrementMajor()`  

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::get "
`get() -> std::string`  

Basic getter for all SBOL literal properties.  

Returns
-------
A string literal  
";

%feature("docstring") sbol::VersionProperty::decrementMinor "
`decrementMinor()`  

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::find "
`find(query) -> bool`  

Check if a value in this property matches the query.  
";

%feature("docstring") sbol::VersionProperty::begin "
`begin() -> iterator`  
";

%feature("docstring") sbol::VersionProperty::addValidationRule "
`addValidationRule(rule)`  
";

%feature("docstring") sbol::VersionProperty::remove "
`remove(index=0)`  

Remove a property value.  
";

%feature("docstring") sbol::VersionProperty::incrementMajor "
`incrementMajor()`  

Increment major version.  
";

%feature("docstring") sbol::VersionProperty::incrementMinor "
`incrementMinor()`  

Increment minor version.  
";

%feature("docstring") sbol::VersionProperty::validate "
`validate(arg=NULL)`  
";

%feature("docstring") sbol::VersionProperty::decrementPatch "
`decrementPatch()`  

Decrement major version.  
";

%feature("docstring") sbol::VersionProperty::incrementPatch "
`incrementPatch()`  

Increment patch version.  
";

%feature("docstring") sbol::VersionProperty::add "
`add(new_value)`  

Appends the new value to a list of values, for properties that allow it.  

Parameters
----------
* `new_value` :  
    A new string which will be added to a list of values.  
";

%feature("docstring") sbol::VersionProperty::getUpperBound "
`getUpperBound() -> char`  
";

%feature("docstring") sbol::VersionProperty::size "
`size() -> int`  
";

%feature("docstring") sbol::VersionProperty::write "
`write()`  
";

%feature("docstring") sbol::VersionProperty::patch "
`patch() -> int`  

Get patch version.  

Returns
-------
The patch version as an integer Splits the version string by a delimiter and
returns the patch version  
";

%feature("docstring") sbol::VersionProperty::getOwner "
`getOwner() -> SBOLObject &`  
";

// File: namespacesbol.xml

%feature("docstring") sbol::libsbol_rule_13 "
`libsbol_rule_13(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::create "
`create() -> sbol::SBOLObject &`  
";

%feature("docstring") sbol::calculateCoverage "
`calculateCoverage(target, qc_annotations) -> float`  
";

%feature("docstring") sbol::libsbol_rule_11 "
`libsbol_rule_11(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::setFileFormat "
`setFileFormat(file_format) -> SBOL_DECLSPEC void`  

Sets file format to use.  
";

%feature("docstring") sbol::getHomespace "
`getHomespace() -> SBOL_DECLSPEC std::string`  

Get the current default namespace for autocreation of URIs when a new SBOL
object is created.  
";

%feature("docstring") sbol::hasHomespace "
`hasHomespace() -> SBOL_DECLSPEC int`  

Checks if a valid default namespace has been defined.  
";

%feature("docstring") sbol::is_alphanumeric_or_underscore "
`is_alphanumeric_or_underscore(c) -> bool`  
";

%feature("docstring") sbol::calculateAmbiguity "
`calculateAmbiguity(target, qc_annotations) -> float`  
";

%feature("docstring") sbol::libsbol_rule_19 "
`libsbol_rule_19(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_18 "
`libsbol_rule_18(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_17 "
`libsbol_rule_17(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_16 "
`libsbol_rule_16(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_15 "
`libsbol_rule_15(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_14 "
`libsbol_rule_14(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::calculateError "
`calculateError(target, qc_annotations) -> float`  
";

%feature("docstring") sbol::libsbol_rule_12 "
`libsbol_rule_12(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::getFileFormat "
`getFileFormat() -> std::string SBOL_DECLSPEC`  

Returns currently accepted file format.  
";

%feature("docstring") sbol::libsbol_rule_10 "
`libsbol_rule_10(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_9 "
`libsbol_rule_9(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_8 "
`libsbol_rule_8(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_3 "
`libsbol_rule_3(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_2 "
`libsbol_rule_2(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_1 "
`libsbol_rule_1(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_7 "
`libsbol_rule_7(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_6 "
`libsbol_rule_6(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_5 "
`libsbol_rule_5(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_4 "
`libsbol_rule_4(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::reportQC "
`reportQC(target, construct, qc_method) -> std::unordered_map< std::string,
    std::tuple< int, int, float > >`  
";

%feature("docstring") sbol::addQCAnnotations "
`addQCAnnotations(target, construct)`  
";

%feature("docstring") sbol::sbolRule10101 "
`sbolRule10101(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::setHomespace "
`setHomespace(ns) -> SBOL_DECLSPEC void`  

Global methods.  

Set the default namespace for autocreation of URIs when a new SBOL object is
created  
";

%feature("docstring") sbol::sbolRule10102 "
`sbolRule10102(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::is_not_alphanumeric_or_underscore "
`is_not_alphanumeric_or_underscore(c) -> bool`  
";

%feature("docstring") sbol::verify_base "
`verify_base(target_base, actual_base) -> std::string`  
";

%feature("docstring") sbol::libsbol_rule_22 "
`libsbol_rule_22(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_20 "
`libsbol_rule_20(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_21 "
`libsbol_rule_21(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::libsbol_rule_24 "
`libsbol_rule_24(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::sbol_rule_10204 "
`sbol_rule_10204(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::calculateIdentity "
`calculateIdentity(target, qc_annotations) -> float`  
";

%feature("docstring") sbol::sbol_rule_10202 "
`sbol_rule_10202(sbol_obj, arg) -> SBOL_DECLSPEC void`  
";

%feature("docstring") sbol::get_sequence_annotation_callback "
`get_sequence_annotation_callback(cdef_node, user_data)`  
";

// File: namespacestd.xml

// File: _biosystem_design_example_8cpp.xml

%feature("docstring") main "
`main() -> int`  
";

// File: _c_r_i_s_p_r_repression_example_8cpp.xml

%feature("docstring") main "
`main() -> int`  
";

// File: _sequence_assembly_example_8cpp.xml

%feature("docstring") main "
`main() -> int`  
";

// File: _find_doxygen_8cmake.xml

// File: getting__started_8dox.xml

// File: installation_8dox.xml

// File: mainpage_8dox.xml

// File: modules_8dox.xml

// File: sequences_8dox.xml

// File: assembly_8cpp.xml

%feature("docstring") std::disassemble "
`disassemble(cdef_node, range_start)`  
";

%feature("docstring") std::compare_ranges "
`compare_ranges(a, b) -> bool`  
";

%feature("docstring") std::is_complete "
`is_complete(cdef_node, user_data)`  
";

%feature("docstring") std::is_regular "
`is_regular(cdef_node, user_data)`  
";

%feature("docstring") std::nest_ranges "
`nest_ranges(ranges, cdef_node, nucleotides)`  
";

// File: assembly_8h.xml

// File: attachment_8h.xml

// File: source_2cmake__install_8cmake.xml

// File: manual_2cmake__install_8cmake.xml

// File: source_2_c_make_lists_8txt.xml

%feature("docstring") include_directories "
`include_directories(${JsonCpp_INCLUDE_DIR})`  
";

%feature("docstring") if "
`if(SBOL_BUILD_SHARED) -> MATCHES Linux OR Darwin`  
";

%feature("docstring") if "
`if(${CMAKE_SYSTEM_NAME} MATCHES \"Windows\")`  
";

%feature("docstring") if "
`if(arg1) -> bigobj EHsc`  
";

%feature("docstring") endif "
`endif()`  
";

%feature("docstring") add_subdirectory "
`add_subdirectory(arg1)`  
";

// File: example_2_c_make_lists_8txt.xml

%feature("docstring") TARGET_LINK_LIBRARIES "
`TARGET_LINK_LIBRARIES(ws2_32)`  
";

%feature("docstring") find_library "
`find_library(arg1)`  
";

%feature("docstring") find_library "
`find_library(arg1)`  
";

%feature("docstring") find_library "
`find_library(arg1)`  
";

%feature("docstring") SET "
`SET(include) -> SBOL lib`  
";

%feature("docstring") SET "
`SET(sbol) -> lib`  
";

%feature("docstring") cmake_policy "
`cmake_policy(NEW)`  
";

// File: manual_2_c_make_lists_8txt.xml

%feature("docstring") CONFIGURE_FILE "
`CONFIGURE_FILE(${SBOL_MANUAL_DIR}/Doxyfile.in ${SBOL_MANUAL_DIR}/)`  
";

// File: collection_8h.xml

// File: combinatorialderivation_8h.xml

// File: component_8h.xml

// File: componentdefinition_8h.xml

// File: config_8cpp.xml

// File: config_8h.xml

// File: constants_8h.xml

// File: dbtl_8cpp.xml

// File: dbtl_8h.xml

// File: document_8cpp.xml

// File: document_8h.xml

// File: identified_8h.xml

// File: implementation_8h.xml

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

// File: partshop_8cpp.xml

%feature("docstring") sbol::getch "
`getch(arg1) -> int`  
";

%feature("docstring") sbol::encode_http "
`encode_http(text)`  
";

%feature("docstring") sbol::replace "
`replace(text, target, replacement)`  
";

%feature("docstring") sbol::http_get_request "
`http_get_request(get_request, headers=NULL, response_headers=NULL) ->
    std::string`  
";

// File: partshop_8h.xml

// File: properties_8cpp.xml

// File: properties_8h.xml

// File: property_8h.xml

// File: provo_8h.xml

// File: sbol_8h.xml

// File: sbolerror_8cpp.xml

// File: sbolerror_8h.xml

// File: sequence_8h.xml

// File: sequenceannotation_8h.xml

// File: sequenceconstraint_8h.xml

// File: toplevel_8h.xml

// File: validation_8cpp.xml

// File: validation_8h.xml

// File: group__sbol__core__data__model.xml

// File: group__extension__layer.xml

// File: getting_started.xml

// File: installation.xml

// File: modular_design.xml

// File: sequences.xml

// File: dir_a2f46d281c6389dc39997ffcf82aba39.xml

// File: dir_ad2b3518b6ff8020e6ece2469bc5e793.xml

// File: dir_f805d5279cb05653177a87a05b432f21.xml

// File: dir_59d233a1711e1dd823533c8983d914f6.xml

// File: dir_42d929c8dbf52848391b2c813969d717.xml

// File: dir_4a2979e7724b3af16c43d59799dc78e7.xml

// File: dir_10125a6defe251d1210214134d64796c.xml

// File: dir_d522931ffa1371640980b621734a4381.xml

// File: indexpage.xml

