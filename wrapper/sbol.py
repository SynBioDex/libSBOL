## @package sbol
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

from libsbol import *

ComponentDefinition.properties = ['roles', 'types']
Design.properties = ['structure', 'function']
SequenceAnnotation.properties = ['roles']

#from libsbol import ComponentDefinition as _ComponentDefinition
#from libsbol import Design as _Design
#
#class PythonicInterface(object):
#
#    def __init__(self):
#        pass
##
##    def __getattribute__(self,name):
##        if name in object.__getattribute__(self, 'properties'):
##            return object.__getattribute__(self, name).get()
##        else:
##            return object.__getattribute__(self, name)
##
##    def __setattribute__(self,name, value):
##        if name in object.__getattribute__(self, 'properties'):
##            object.__getattribute__(self, name).set(value)
##        else:
##            object.__setattribute__(self, name, value)
#
#class ComponentDefinition(_ComponentDefinition):
#    properties = ['roles']
#
#    def __init__(self, *args):
#        super(self.__class__, self).__init__(*args)
#        #PythonicInterface.__init__(self)
#
#    def __getattribute__(self,name):
#        if name in object.__getattribute__(self, 'properties'):
#            return object.__getattribute__(self, name).get()
#        else:
#            return object.__getattribute__(self, name)
#
#    def __setattr__(self,name, value):
#        if name in object.__getattribute__(self, 'properties'):
#            object.__getattribute__(self, name).set(value)
#        else:
#            object.__setattr__(self, name, value)
#
#class Design(_Design):
#    properties = ['structure', 'function']
#    
#    def __init__(self, *args):
#        super(self.__class__, self).__init__(*args)
#    #PythonicInterface.__init__(self)
#    
#    def __getattribute__(self,name):
#        if name in object.__getattribute__(self, 'properties'):
#            return object.__getattribute__(self, name).get()
#        else:
#            return object.__getattribute__(self, name)
#
#    def __setattr__(self,name, value):
#        if name in object.__getattribute__(self, 'properties'):
#            object.__getattribute__(self, name).set(value)
#        else:
#            object.__setattr__(self, name, value)
#
