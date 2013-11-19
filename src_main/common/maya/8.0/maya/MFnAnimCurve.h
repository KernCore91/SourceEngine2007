
#ifndef _MFnAnimCurve
#define _MFnAnimCurve
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MFnAnimCurve
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnAnimCurve)
//
//	In Maya Animation Curves (Anim Curves) are implemented as Dependency Graph
//	(DG) Nodes.  Each Node has multiple ordered and indexed keyframes.
//
//	There are 8 different types of Anim Curve nodes:
//		timeToAngular (animCurveTA)
//		timeToLinear (animCurveTL)
//		timeToTime (animCurveTT)
//		timeToUnitless (animCurveTU)
//		unitlessToAngular (animCurveUA)
//		unitlessToLinear (animCurveUL)
//		unitlessToTime (animCurveUT)
//		unitlessToUnitless (animCurveUU)
//	Specifying the correct AnimCurveType during creation will avoid implicit
//	unit conversions.
//
//	The Anim Curve Function Set provides methods for creating, querying and
//	editing Anim Curve Nodes and the keyframes which are internal to the Nodes.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MFnDependencyNode.h>
#include <maya/MTime.h>
#include <maya/MAngle.h>
#include <maya/MDoubleArray.h>
#include <maya/MTimeArray.h>

// *****************************************************************************

// DECLARATIONS

class MAnimCurveChange;
class MPlug;
class MDGModifier;

// *****************************************************************************

// CLASS DECLARATION (MFnAnimCurve)

///  Anim Curve Function Set (OpenMayaAnim)
/**

Create, query and edit Anim Curve Nodes and the keys internal to
those Nodes.

Create an Anim Curve Node and connect its output to any animatable
attribute on another Node.

Evaluate an Anim Curve at a particular time.

Determine the number of keys held by an Anim Curve.

Determine the time and value of individual keys, as well as the
(angle,weight) or (x,y) values and type of key tangents.  The in-tangent
refers to the tangent entering the key.  The out-tangent refers to the tangent
leaving the key.

Find the index of the key at, or closest to a particular time.

Set the time and value of individual keys, as well as the type of
the tangent to the curve entering (in-tangent) and leaving
(out-tangent) the key, specify the tangent as either (angle,weight) or (x,y).

Add and remove keys from an Anim Curve.

*/
#ifdef _WIN32
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYAANIM_EXPORT MFnAnimCurve : public MFnDependencyNode
{
	declareMFn(MFnAnimCurve, MFnDependencyNode);
public:
	///
	MFnAnimCurve (const MPlug &plug, MStatus *ReturnStatus = NULL);

public:
	///
	enum AnimCurveType {
		/// kAnimCurveTA = 0
		kAnimCurveTA = 0,
		/// kAnimCurveTL
		kAnimCurveTL,
		/// kAnimCurveTT
		kAnimCurveTT,
		/// kAnimCurveTU
		kAnimCurveTU,
		/// kAnimCurveUA
		kAnimCurveUA,
		/// kAnimCurveUL
		kAnimCurveUL,
		/// kAnimCurveUT
		kAnimCurveUT,
		/// kAnimCurveUU
		kAnimCurveUU,
		/// kAnimCurveUnknown
		kAnimCurveUnknown
	};
    ///
	enum TangentType {
        ///
		kTangentGlobal = 0,
        ///
		kTangentFixed,
        ///
		kTangentLinear,
        ///
		kTangentFlat,
        ///
		kTangentSmooth,
        ///
		kTangentStep,
        ///OBSOLETE kTangentSlow should not be used. Using this tangent type may produce unwanted and unexpected results.
		kTangentSlow,
        ///OBSOLETE kTangentFast should not be used. Using this tangent type may produce unwanted and unexpected results.
		kTangentFast,
        ///
		kTangentClamped,
		///
		kTangentPlateau,
        ///
        kTangentStepNext
    };
    ///
    enum InfinityType {
		///
		kConstant = 0,
		///
		kLinear = 1,
		///
		kCycle = 3,
		///
		kCycleRelative = 4,
		///
		kOscillate = 5
	};
	///
	MObject     create( const MObject & node,
						const MObject & attribute,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	///
	MObject     create( const MObject & node,
						const MObject & attribute,
						AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
    ///
	MObject     create( MPlug & plug,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
    ///
	MObject     create( MPlug & plug,
						AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	///
	//	the following create method builds an animCurve with
	//	no connections
	MObject		create( AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );

	///
	AnimCurveType	animCurveType (MStatus *ReturnStatus = NULL) const;

	///
	AnimCurveType   timedAnimCurveTypeForPlug( MPlug& plug,
											   MStatus *ReturnStatus = NULL) const;

	///
	AnimCurveType   unitlessAnimCurveTypeForPlug( MPlug& plug,
											   MStatus *ReturnStatus = NULL) const;

    ///
	double      evaluate( const MTime &atTime,
						  MStatus * ReturnStatus = NULL ) const;
    ///
	MStatus		evaluate( const MTime &atTime, double &value ) const;
	///
	MStatus		evaluate( const MTime &atTime, MTime &timeValue ) const;
	///
	MStatus		evaluate( const double &atUnitlessInput, double &value ) const;
	///
	MStatus		evaluate( const double &atUnitlessInput,
						  MTime &timeValue ) const;
	///
	bool		isStatic( MStatus * ReturnStatus = NULL ) const;
	///
	unsigned int    numKeyframes( MStatus * ReturnStatus = NULL ) const;
    ///
	unsigned int	numKeys( MStatus * ReturnStatus = NULL ) const;
    ///
	MStatus     remove( unsigned int index, MAnimCurveChange * change = NULL );
    ///
	MStatus     addKeyframe( MTime time, double value,
							 MAnimCurveChange * change = NULL );
    ///
	MStatus     addKeyframe( MTime time, double value,
							 TangentType tangentInType,
							 TangentType tangentOutType,
							 MAnimCurveChange * change = NULL );
	///
	// for animCurveTU, animCurveTL and animCurveTA
	unsigned int	addKey( MTime time, double value,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	///
	// for animCurveTT
	unsigned int	addKey( MTime timeInput, MTime timeValue,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	///
	// for animCurveUU, animCurveUL and animCurveUA
	unsigned int	addKey( double unitlessInput, double value,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	///
	// for animCurveUT
	unsigned int	addKey( double unitlessInput, MTime time,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	///
	// block add keys for TL, TA and TU animCurves
	MStatus		addKeys( MTimeArray * timeArray,
						 MDoubleArray * valueArray,
						 TangentType tangentInType = kTangentGlobal,
						 TangentType tangentOutType = kTangentGlobal,
						 bool keepExistingKeys = false,
							 MAnimCurveChange * change = NULL );

    ///
	bool        find( MTime time, unsigned int &index,
					         MStatus * ReturnStatus = NULL ) const;
    ///
	bool		find( double unitlessInput, unsigned int & index,
					  MStatus * ReturnStatus = NULL ) const;
    ///
	unsigned int    findClosest( MTime time, MStatus * ReturnStatus = NULL ) const;
    ///
	unsigned int	findClosest( double unitlessInput,
							 MStatus * ReturnStatus = NULL ) const;
    ///
	MTime       time( unsigned int index, MStatus * ReturnStatus = NULL ) const;
    ///
	double      value( unsigned int index, MStatus * ReturnStatus = NULL ) const;
    ///
	double		unitlessInput( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
	///
	MStatus     setValue( unsigned int index, double value,
					   	  MAnimCurveChange * change = NULL );
    ///
	MStatus     setTime( unsigned int index, MTime time,
						 MAnimCurveChange * change = NULL );
    ///
    MStatus		setUnitlessInput( unsigned int index, double unitlessInput,
								  MAnimCurveChange * change = NULL );
	///
	bool		isTimeInput( MStatus * ReturnStatus = NULL ) const;
    ///
	bool		isUnitlessInput( MStatus * ReturnStatus = NULL ) const;
    ///
	TangentType inTangentType( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
    ///
	TangentType outTangentType( unsigned int index,
								MStatus * ReturnStatus = NULL ) const;
    ///
	MStatus     setInTangentType( unsigned int index, TangentType tangentType,
								  MAnimCurveChange * change = NULL );
    ///
	MStatus     setOutTangentType( unsigned int index, TangentType tangentType,
								   MAnimCurveChange * change = NULL );
	///
	MStatus     getTangent( unsigned int index, float &x, float &y,
							bool inTangent ) const;
	///
	MStatus     getTangent( unsigned int index, MAngle &angle, double &weight,
							bool inTangent ) const;
    ///
    MStatus		setTangent( unsigned int index, float x, float y, bool inTangent,
						   	MAnimCurveChange * change = NULL );
	///
    MStatus		setTangent( unsigned int index, MAngle angle, double weight,
							bool inTangent, MAnimCurveChange * change = NULL );
    ///
	MStatus		setAngle( unsigned int index, MAngle angle, bool inTangent,
						  MAnimCurveChange * change = NULL );
    ///
	MStatus		setWeight( unsigned int index, double weight, bool inTangent,
						   MAnimCurveChange * change = NULL );
    ///
	bool		weightsLocked( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
	///
	bool		tangentsLocked( unsigned int index,
								MStatus * ReturnStatus = NULL ) const;
	///
	MStatus		setWeightsLocked( unsigned int index, bool locked,
								  MAnimCurveChange * change = NULL );
	///
	MStatus		setTangentsLocked( unsigned int index, bool locked,
								   MAnimCurveChange * change = NULL );
	///
	InfinityType	preInfinityType( MStatus * ReturnStatus = NULL ) const;
	///
	InfinityType	postInfinityType( MStatus * ReturnStatus = NULL ) const;
	///
	MStatus		setPreInfinityType( InfinityType infinityType,
									MAnimCurveChange * change = NULL );
	///
	MStatus		setPostInfinityType( InfinityType infinityType,
									 MAnimCurveChange * change = NULL );
	///
	bool		isWeighted (MStatus *ReturnStatus = NULL) const;
	///
	MStatus		setIsWeighted (bool isWeighted,
							   MAnimCurveChange *change = NULL);
	///
	bool		isBreakdown( unsigned int index,
							 MStatus * ReturnStatus = NULL ) const;
	///
	MStatus		setIsBreakdown( unsigned int index,
								bool isBreakdown,
								MAnimCurveChange *change = NULL);

protected:
// No protected members

private:
// No private members

// *****************************************************************************
};

#ifdef _WIN32
#pragma warning(default: 4522)
#endif // _WIN32

#endif /* __cplusplus */
#endif /* _MFnAnimCurve */