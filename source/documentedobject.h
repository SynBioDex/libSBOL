/// @defgroup SBOLCompoundObject SBOLCompoundObject
/// @{
/// @struct _SBOLCompoundObject
/// @brief SBOLObject that also includes a name,
/// displayID, and description.
/// @details Used a base struct for DNAComponent and Collection.
/// @var _SBOLCompoundObject::base
/// @var _SBOLCompoundObject::displayID
/// @var _SBOLCompoundObject::name
/// @var _SBOLCompoundObject::description

#ifndef SBOL_DOCUMENTED_HEADER
#define SBOL_DOCUMENTED_HEADER

struct _DocumentedObject {
	const char* __class;
	TextProperty* displayID;   ///< Like the uri but for display purposes. Not necessarily unique.
	TextProperty* name;        ///< Like the uri but human-readable. Not necessarily unique.
	TextProperty* description; ///< Some text describing the object.
	void *subclass;
};

/// @name Methods
/// @{

///// Create an empty SBOLCompoundObject.
///// @return A pointer to the new SBOLCompoundObject.
//SBOLCompoundObject* createSBOLCompoundObject(Document* doc, const char* uri);
//
///// Delete an SBOLObject.
///// This shouldn't be called directly;
///// instead, use deleteDNAComponent, deleteCollection, etc.
//void deleteSBOLCompoundObject(SBOLCompoundObject* obj);
//
///// Set the URI of an SBOLComoundObject.
///// This shouldn't be called directly.
//void setSBOLCompoundObjectURI(SBOLCompoundObject* obj, const char* uri);
//
///// Get the URI of an SBOLCompoundObject.
///// This shouldn't be called directly.
//char* getSBOLCompoundObjectURI(const SBOLCompoundObject* obj);
//
///// Set the displayID of an SBOLCompoundObject.
///// This shouldn't be called directly.
///// Gotcha: uppercase D
//void setSBOLCompoundObjectDisplayID(SBOLCompoundObject* obj, const char* id);
//
///// Get the URI of an SBOLCompoundObject.
///// This shouldn't be called directly.
///// Gotcha: uppercase D
//char* getSBOLCompoundObjectDisplayID(const SBOLCompoundObject* obj);
//
///// Set the name of an SBOLCompoundObject.
///// This shouldn't be called directly.
//void setSBOLCompoundObjectName(SBOLCompoundObject* obj, const char* name);
//
///// Get the name of an SBOLCompoundObject.
///// This shouldn't be called directly.
//char* getSBOLCompoundObjectName(const SBOLCompoundObject* obj);
//
///// Set the description of an SBOLCompoundObject.
///// This shouldn't be called directly.
//void setSBOLCompoundObjectDescription(SBOLCompoundObject* obj, const char* descr);
//
///// Get the description of an SBOLCompoundObject.
///// This shouldn't be called directly.
//char* getSBOLCompoundObjectDescription(const SBOLCompoundObject* obj);
//
///// @}
///// @}
//
#endif
