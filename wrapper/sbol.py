# @package sbol
# A Python wrapper for libSBOLc, a module for reading, writing, and constructing
# genetic designs according to the standardized specifications of the Synthetic Biology Open Language
#
# @file sbol.py
# Implements a high-level, Pythonic interface for the SWIG-Python classes in libsbol
#
# @namespace sbol.sbol
# High level wrappers for libSBOLc
#
# @namespace sbol.libsbol
# Low level SWIG-Python wrappers for libSBOLc
#
# @namespace sbol.sbol_test
# Unit tests

from .libsbol import *

__Activity__ = Activity  # Import and rename the core SBOL Activity class 

class Activity(__Activity__):
	"""


	Extends the Activity class in the core SBOL library, libsbol.  Particularly, 
	it adds convenience methods for constructing design-build-test-learn workflows out 
	of Activity objects.  

	"""
	def __init__(self, uri, version = VERSION_STRING):
		"""


		Construct an Activity  

		Parameters
		----------
		* `uri` :  
			A unique identifier for the object. If the `sbol_compliant_uris` option 
			configuration is enabled (default), then the user should pass a simple 
			identifier for the new object and a full URI will automatically be 
			constructed. Otherwise the user muste specify the full URI, including a 
			scheme, namespace, and identifier.   
		* `version` :  
			An arbitrary version string that corresponds to Maven versioning semantics

		"""
		__Activity__.__init__(self, PROVO_ACTIVITY, uri, "", version)



	def generateDesign(self, uris, analysis_usages, design_usages = None):
		"""


		Generate one or more Design objects  

		Parameters
		----------
		* `uris` :  
			One or more identifiers for the new Design object(s). If the 
			`sbol_compliant_uris` option configuration is enabled, then the user 
			should specify simple identifiers for the objects. Otherwise the user 
			must provide full URIs each consisting of a scheme, namespace, and identifier. 
		* `analysis_usages` :  
			A singleton Analysis object, list of Analysis objects, or None. Analysis usages
			represent a prediction or forward-specification of the new Design's intended 
			structure or function.  
		* `design_usages` :  
			A singleton Design object, list of Design objects, or None. Design usages may 
			represent previous Designs that are being tranformed or composed into 
			the new Design.

		Returns
		-------
		A singleton Design or list of Designs depending on whether the user specifies
		a single URI or list of URIs.  

		"""

		self.__validate_activity__(SBOL_DESIGN)
		if type(uris) != list:
			uris = [ uris ]
		for uri in uris:
			if type(uri) != str:
				raise TypeError('Cannot generate Design. The first argument must be a string or list of strings')
		if len(uris) != len(set(uris)):
			raise ValueError('Cannot generate Design. The first argument cannot contain duplicate values')

		try:
			analysis_usages = self.__validate_usages__(analysis_usages, Analysis)
		except TypeError:
			raise TypeError('Cannot generate Design. The second argument must be an Analysis or list of Analyses')
		
		try:
			design_usages = self.__validate_usages__(design_usages, Design)
		except TypeError:
			raise TypeError('Cannot generate Design. The third argument must be a Design or list of Designs')

		if not len(analysis_usages) and not len(design_usages):
			raise ValueError('Cannot generate Design. User must specify usages of either Analysis or Design type')

		new_designs = []
		for uri in uris:			
			new_design = self.doc.designs.create(uri)
			new_design.wasGeneratedBy = self.identity
			if len(analysis_usages):
				new_design.specification = analysis_usages[0]
			new_designs.append(new_design)

		self.__create_usages__(analysis_usages)
		self.__create_usages__(design_usages)

		if len(new_designs) > 1:
			return new_designs
		else:
			return new_designs[0]

	def generateBuild(self, uris, design_usages, build_usages = None):
		"""


		Generate one or more Build objects  

		Parameters
		----------
		* `uris` :  
			One or more identifiers for the new Build object(s). If the 
			`sbol_compliant_uris` option configuration is enabled, then the user 
			should specify simple identifiers for the objects. Otherwise the user 
			must provide full URIs each consisting of a scheme, namespace, and identifier. 
		* `design_usages` :  
			A singleton Design object, list of Design objects, or None. Design usages represent
			the engineer's intent or "blueprint" for the Build target. 
		* `build_usages` :  
			A singleton Build object, list of Build objects, or None. Build usages
			represent physical components, such as laboratory samples, that are assembled
			into the target Build.  

		Returns
		-------
		A singleton Build or list of Builds depending on whether the user specifies
		a single URI or list of URIs.  

		"""
		self.__validate_activity__(SBOL_BUILD)
		if type(uris) != list:
			uris = [ uris ]

		for uri in uris:
			if type(uri) != str:
				raise TypeError('Cannot generate Build. The first argument must be a string or list of strings')
		if len(uris) != len(set(uris)):
			raise ValueError('Cannot generate Build. The first argument cannot contain duplicate values')

		try:
			design_usages = self.__validate_usages__(design_usages, Design)
		except TypeError:
			raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
		
		try:
			build_usages = self.__validate_usages__(build_usages, Build)
		except TypeError:
			raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

		if not len(design_usages) and not len(build_usages):
			raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

		new_builds = []
		for uri in uris:
			new_build = self.doc.builds.create(uri)
			new_build.wasGeneratedBy = self.identity
			if len(design_usages):
				new_build.design = design_usages[0]
			new_builds.append(new_build)

		self.__create_usages__(design_usages)
		self.__create_usages__(build_usages)
		
		if len(new_builds) > 1:
			return new_builds
		else:
			return new_builds[0]


	def generateTest(self, uris, build_usages, test_usages = None):
		"""


		Generate one or more Test objects  

		Parameters
		----------
		* `uris` :  
			One or more identifiers for the new Test object(s). If the 
			`sbol_compliant_uris` option configuration is enabled, then the user 
			should specify simple identifiers for the objects. Otherwise the user 
			must provide full URIs each consisting of a scheme, namespace, and identifier. 
		* `build_usages` :  
			A singleton Build object, list of Build objects, or None. Build usages represent
			samples or analytes used in an experimental measurement.
		* `test_usages` :  
			A singleton Test object, list of Test objects, or None. Test usages
			represent other measurements or raw data that the user wants to integrate into
			a single data set.
		
		Returns
		-------
		A singleton Test or list of Tests depending on whether the user specifies
		a single URI or list of URIs.  

		"""
		self.__validate_activity__(SBOL_TEST)

		if type(uris) != list:
			uris = [ uris ]
		for uri in uris:
			if type(uri) != str:
				raise TypeError('Cannot generate Test. The first argument must be a string or list of strings')
		if len(uris) != len(set(uris)):
			raise ValueError('Cannot generate Test. The first argument cannot contain duplicate values')

		if type(build_usages) == SampleRoster:
			build_usages = [ build_usages ]
		else:
			try:
				build_usages = self.__validate_usages__(build_usages, Build)
			except TypeError:
				raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
		
		try:
			test_usages = self.__validate_usages__(test_usages, Test)
		except TypeError:
			raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

		if not len(build_usages) and not len(test_usages):
			raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

		new_tests = []
		for uri in uris:
			new_test = self.doc.tests.create(uri)
			new_test.wasGeneratedBy = self.identity
			if len(build_usages):
				new_test.samples = build_usages
			new_tests.append(new_test)

		self.__create_usages__(build_usages)
		self.__create_usages__(test_usages)
		if len(new_tests) > 1:
			return new_tests
		else:
			return new_tests[0]

	def generateAnalysis(self, uris, test_usages, analysis_usages = None):
		"""


		Generate one or more Analysis objects.

		Parameters
		----------
		* `uris` :  
			One or more identifiers for the new Analysis object(s). If the 
			`sbol_compliant_uris` option configuration is enabled, then the user 
			should specify simple identifiers for the objects. Otherwise the user 
			must provide full URIs each consisting of a scheme, namespace, and identifier. 
		* `test_usages` :  
			A singleton Test object, list of Test objects, or None. Test usages represent
			raw experimental data used to generate an Analysis.
		* `analysis_usages` :  
			A singleton Analysis object, list of Analysis objects, or None. Analysis usages
			represent other analyses that the user wants to integrate into
			a single data set or data sheet.

		Returns
		-------
		A singleton Analysis or list of Analyses depending on whether the user specifies
		a single URI or list of URIs.

		"""
		self.__validate_activity__(SBOL_TEST)

		if type(uris) != list:
			uris = [ uris ]
		for uri in uris:
			if type(uri) != str:
				raise TypeError('Cannot generate Analysis. The first argument must be a string or list of strings')
		if len(uris) != len(set(uris)):
			raise ValueError('Cannot generate Analysis. The first argument cannot contain duplicate values')

		try:
			test_usages = self.__validate_usages__(test_usages, Test)
		except TypeError:
			raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
		
		try:
			analysis_usages = self.__validate_usages__(analysis_usages, Analysis)
		except TypeError:
			raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

		if not len(test_usages) and not len(analysis_usages):
			raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

		new_analyses = []
		for uri in uris:
			new_analysis = self.doc.analyses.create(uri)
			new_analysis.wasGeneratedBy = self.identity
			if len(test_usages):
				new_analysis.rawData = test_usages[0]
			new_analyses.append(new_analysis)

		self.__create_usages__(test_usages)
		self.__create_usages__(analysis_usages)
		if len(new_analyses) > 1:
			return new_analyses
		else:
			return new_analyses[0]

	def __validate_activity__(self, activity_type):
		if not self.doc : raise ValueError('Failed to generate. This Activity must first be added to a Document')
		if len(self.associations):
			for a in self.associations:
				if not a.agent: 
					raise ValueError('Failed to generate. This Activity does not specify an Agent')
				if not a.plan:
					raise ValueError('Failed to generate. This Activity does not specify a Plan')
			for a in self.associations:
				a.roles = activity_type 
		else:
			raise ValueError('Failed to generate. This Activity does not specify an Agent or Plan')

	def __validate_usages__(self, usage_list, UsageType):
		if usage_list == None:
			usage_list = []
		elif type(usage_list) != list:
			usage_list = [ usage_list ]
		for u in usage_list:
			if not type(u) == UsageType:
				raise TypeError()
		return usage_list    	

	def __create_usages__(self, usage_list):
		for u in usage_list:
			if not u.doc:
				if type(u == Design):
					self.doc.addDesign(u)
				if type(u == Build):
					self.doc.addBuild(u)
				elif type(u == Test):
					self.doc.addTest(u)
				elif type(u == Analysis):
					self.doc.addAnalsis(u)
				elif type(u == SampleRoster):
					self.doc.addTest(u)
			if Config.getOption('sbol_compliant_uris') == 'True':
				id = u.displayId
			else:
				id = u.identity
			U = self.usages.create(id + '_usage');
			U.entity = u.identity
			U.roles = Activity.usage_map[type(u)]

	usage_map = \
		{
			Design : SBOL_URI + "#design",
			Build : SBOL_URI + "#build",
			Test : SBOL_URI + "#test",
			Analysis : SBOL_URI + "#learn",
			SampleRoster : SBOL_URI + "#build"
		}
