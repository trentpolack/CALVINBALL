// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#pragma once

#define ENUMERATE_PROPERTY_TYPES( Op )		\
			Op( int16, UInt16Property )		\
			Op( int32, UIntProperty )		\
			Op( int64, UInt64Property )		\
			Op( uint16, UUInt16Property )	\
			Op( uint32, UUInt32Property )	\
			Op( uint64, UUInt64Property )	\
			Op( float, UFloatProperty )		\

template< typename T > struct FJoyValuePropertyType;

#define MAP_PROPERTY_TYPE( CppType, UEType )			\
template<> struct FJoyValuePropertyType< CppType >		\
{														\
	typedef class UEType PropertyType;					\
};

ENUMERATE_PROPERTY_TYPES( MAP_PROPERTY_TYPE )

#undef MAP_PROPERTY_TYPE