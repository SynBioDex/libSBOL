/**
 * @file    location.h
 * @brief   Location, Cut, Range, and GenericLocation classes
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

#ifndef LOCATION_INCLUDED
#define LOCATION_INCLUDED

#include "identified.h"

namespace sbol
{
    /// The Location class specifies the strand orientation of a Component and can be further extended by the Range, Cut, and GenericLocation classes.
	class SBOL_DECLSPEC Location : public Identified
	{
	public:
        // A public constructor is required so objects can be auto created by the SBOLObject.OwnedObjects.create(...) method
        Location(rdf_type type = SBOL_LOCATION, std::string uri = "example", std::string orientation = SBOL_ORIENTATION_INLINE) :
            Identified(type, uri),
            orientation(this, SBOL_ORIENTATION, '1', '1', ValidationRules({}), orientation),
            sequence(this, SBOL_SEQUENCE_PROPERTY, SBOL_SEQUENCE, '0', '1', ValidationRules({}))
            {
            }
        
        /// The orientation indicates how a region of double-stranded DNA represented by the parent SequenceAnnotation and its associated Component are oriented. The orientation may be one of the following values. By default it is set to SBOL_ORIENTATION_INLINE.
        /// | Orientation URI                       | libSBOL Symbol                      |
        /// | :------------------------------------ | :---------------------------------- |
        /// | http://sbols.org/v2#inline            | SBOL_ORIENTATION_INLINE             |
        /// | http://sbols.org/v2#reverseComplement | SBOL_ORIENTATION_REVERSE_COMPLEMENT |
        URIProperty orientation;

        /// Links a Location to the Sequence it is annotating, in case the parent ComponentDefinition has multiple Sequences and it is ambiguous which Sequence the Location is referring to
        ReferencedObject sequence;
        
        virtual ~Location() {};;
    };

    /// A Range object specifies a region via discrete, inclusive start and end positions that correspond to indices for characters in the elements String of a Sequence.  Note that the index of the first location is 1, as is typical practice in biology, rather than 0, as is typical practice in computer science.
	class SBOL_DECLSPEC Range : public Location
	{
	public:
        /// Construct a Range. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < Range > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param start An integer of 1 or greater
        /// @param end An integer equal to or greater than the start
        Range(std::string uri = "example", int start = 1, int end = 2) : Range(SBOL_RANGE, uri, start, end) {};
        
        /// Specifies the inclusive starting position of a sequence region. It must be 1 or greater.
		IntProperty start;
        
        /// Specifies the inclusive end position of a sequence region. It must be equal to or greater than the start.
		IntProperty end;

        /// Calculates how many bases separate these Ranges
        /// @comparand Another Range object
        /// @return The number of bases by which this Range precedes the comparand, or 0 if it does not precede
        int precedes(Range& comparand);

        /// Calculates how many bases separate these Ranges
        /// @comparand Another Range object
        /// @return The number of bases by which this Range follows the comparand, or 0 if it does not follow
        int follows(Range& comparand);

        /// Calculates how many bases of the comparand are contained by this Range.
        /// @comparand Another Range object
        /// @return The number of bases which are contained (equivalent to the length of the comparand), or 0 if it is not contained.
        int contains(Range& comparand);

        /// Calculates how many bases separate this Range from the comparand.
        /// @comparand Another Range object
        /// @return The number of bases by which the Ranges overlap. If they overlap, this is always a positive number regardless of direction. If they do not overlap, returns zero
        int overlaps(Range& comparand);
        
        /// Returns the length of a Range
        int length();

        /// Indicate if these Ranges represent adjacent intervals.
        /// @comparand Another Range object
        /// @return 1 if these Ranges adjoin or border each other, 0 if they are separated by an intervening Range
        int adjoins(Range& comparand);

        virtual ~Range() {};
        
	protected:
        Range(rdf_type type, std::string uri, int start, int end) :
            Location(type, uri),
            start(this, SBOL_START, '1', '1', ValidationRules({}), start),
            end(this, SBOL_END, '1', '1', ValidationRules({}), end)
            {
            };
	};

    /// The Cut class specifies a location between two coordinates of a Sequence's elements.     class Cut : public Location
    class SBOL_DECLSPEC Cut : public Location
    {
    public:
        /// Construct a Cut. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < Cut > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param at An integer of 0 or greater
        Cut(std::string uri = "example", int at = 0) : Cut(SBOL_CUT, uri, at) {};

        /// This property specifies the location between this nucleotide coordinate (or other sequence element) and the nucleotide coordinate immediately following it. When equal to zero, the specified region is immediately before the first nucleotide or character in the elements
        IntProperty at;
        
        virtual ~Cut() {};
        
    protected:
        Cut(rdf_type type, std::string uri, int at) :
            Location(type, uri),
            at(this, SBOL_AT, '1', '1', ValidationRules({}), at)
        {
        };

    };

    /// the GenericLocation class is included as a starting point for specifying regions on Sequence objects with encoding properties other than IUPAC and potentially nonlinear structure. This class can also be used to set the orientation of a SequenceAnnotation and any associated Component when their parent ComponentDefinition is a partial design that lacks a Sequence.
    class SBOL_DECLSPEC GenericLocation : public Location
    {
    public:
        /// Construct a GenericLocation. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < GenericLocation > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        GenericLocation(std::string uri = "example") : GenericLocation(SBOL_GENERIC_LOCATION, uri) {};
        
        virtual ~GenericLocation() {};
        
    protected:
        GenericLocation(rdf_type type, std::string uri) :
            Location(type, uri)
        {
        };
        
    };

}



#endif
