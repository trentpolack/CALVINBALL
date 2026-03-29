// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#include "JoyObjectSerialization.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#include "JoySerializationInternal.h"

#include "JoyObjectDeserialization.h"

/*
*	IJoySerializeValueProperty Interface Definition.
*/
class IJoySerializeValueProperty
{
public:
	virtual bool IsValidProperty( UProperty* Property ) const = 0;
	virtual void SerializeProperty( TSharedPtr< FJsonValue >& JSONObjectValue, const uint8* PropertyValue ) const = 0;
};

/*
 *	FJoySerializeValueProperty Class Definition (I hate doing this in a CPP file).
*/
template < typename T >
class FJoySerializeValueProperty : public IJoySerializeValueProperty
{
protected:
	typedef typename FJoyValuePropertyType< T >::PropertyType PropertyType;

public:
	virtual bool IsValidProperty( UProperty* Property ) const
	{
		return Property->IsA( PropertyType::StaticClass() );
	}

	virtual void SerializeProperty( TSharedPtr< FJsonValue >& JSONObjectValue, const uint8* PropertyValue ) const
	{
		const T value = *( const T* )PropertyValue;
		JSONObjectValue = MakeShareable( new FJsonValueNumber( value ) );
	}
};

//----------------------------------------------------------------------------------------------------
FJoyObjectSerialization::FJoyObjectSerialization( )
{	}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectSerialization::SerializeDataToJson( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, TSharedPtr< FJsonValue >& JSONObjectValue, bool SerializeClassName, int32 PortFlags )
{
	if( !ObjectData )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Invalid ObjectData during serialization to JSON. Aborting." ) );
		return false;
	}

	if( !ObjectClass )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Invalid ObjectClass during serialization to JSON. Aborting." ) );
		return false;
	}

	FJoyObjectSerialization::Serialize( JSONObjectValue, ObjectClass, ObjectData, Parent, PortFlags, SerializeClassName );
	if( !JSONObjectValue.IsValid( ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Unable to serialization object value to JSON (ObjectClass: %s). Aborting." ), *ObjectClass->GetName( ) );
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectSerialization::SerializeDataToJsonString( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, FString& JSONString, bool SerializeClassName, int32 PortFlags )
{
	if( !ObjectData )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Invalid ObjectData during serialization to string. Aborting." ) );
		return false;
	}

	if( !ObjectClass )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Invalid ObjectClass during serialization to string. Aborting." ) );
		return false;
	}

	TSharedPtr< FJsonValue > JSONObjectValue;
	if( FJoyObjectSerialization::SerializeDataToJson( ObjectData, ObjectClass, Parent, JSONObjectValue, SerializeClassName, PortFlags ) )
	{
		TSharedPtr< FJsonObject > JSONObject = JSONObjectValue->AsObject( );
		TSharedRef< TJsonWriter< > > Writer = TJsonWriterFactory< >::Create( &JSONString );
		if( !FJsonSerializer::Serialize( JSONObject.ToSharedRef( ), Writer ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Unable to serialization object value to string (ObjectClass: %s). Aborting." ), *ObjectClass->GetName( ) );
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::Serialize( TSharedPtr< FJsonValue >& JSONObjectValue, UStruct* ObjectClass, const uint8* ObjectData, UObject* Parent, int32 PortFlags, bool SerializeClassName )
{
	TSharedPtr< FJsonObject > JSONObject = MakeShareable( new FJsonObject( ) );
	check( ObjectClass );

	if( SerializeClassName )
	{
		// Add class property before other properties for readability
		JSONObject->Values.Add( TEXT( "Class" ), MakeShareable( new FJsonValueString( ObjectClass->GetName( ) ) ) );
	}

	// Serialize the object class' properties.
	for( UProperty* Property = ObjectClass->PropertyLink; Property; Property = Property->PropertyLinkNext )
	{
		if( Property->ShouldPort( PortFlags ) )
		{
			UObjectPropertyBase* SerializeObjectProp = ( ( Property->PropertyFlags & CPF_ExportObject ) != 0 ) ? Cast< UObjectPropertyBase >( Property ) : nullptr;

			TSharedPtr< FJsonValue > JSONObjectPropertyValue = nullptr;
			SerializeProperty( JSONObjectPropertyValue, Property, Property->ContainerPtrToValuePtr< uint8 >( ObjectData ), nullptr, Parent, PortFlags, -1, nullptr );
			if( JSONObjectPropertyValue.IsValid( ) )
			{
				JSONObject->Values.Add( Property->GetName( ), JSONObjectPropertyValue );
			}
		}
	}

	JSONObjectValue = MakeShareable( new FJsonValueObject( JSONObject ) );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializeProperty( TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, int32 ArrayIndex, UObject* SerializeRootScope )
{
	// Static list of number converters.

#define STATIC_JSON_CONVERTER( CppType, UEType ) \
	static const FJoySerializeValueProperty< CppType > JSONValueSerializer_##UEType;

	ENUMERATE_PROPERTY_TYPES( STATIC_JSON_CONVERTER )

#undef STATIC_JSON_CONVERTER

#define STATIC_JSON_CONVERTER_ELEMENT( CppType, UEType ) &JSONValueSerializer_##UEType,

	// A corresponding static list of converter base class pointers
	static const IJoySerializeValueProperty* JSONValueSerializers[] =
	{
		ENUMERATE_PROPERTY_TYPES( STATIC_JSON_CONVERTER_ELEMENT )
	};

#undef STATIC_JSON_CONVERTER_ELEMENT

	// Handle number properties.
	static const uint32 serializerCount = sizeof( JSONValueSerializers )/sizeof( JSONValueSerializers[0] );
	bool handled = false;
	for ( uint32 i = 0 ; i < serializerCount ; ++i )
	{
		const IJoySerializeValueProperty* converter = JSONValueSerializers[i];
		if( converter->IsValidProperty( Property ) )
		{
			converter->SerializeProperty( JSONObjectValue, PropertyValue );
			return;
		}
	}

	// Handle non-numerical properties.
	if( Property->IsA( UBoolProperty::StaticClass( ) ) )
	{
		SerializePropertyBool( JSONObjectValue, Cast< UBoolProperty >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	}
	else if( Property->IsA( UByteProperty::StaticClass( ) ) )
	{
		SerializePropertyByte( JSONObjectValue, Cast< UByteProperty >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	}
	else if( Property->IsA( UObjectPropertyBase::StaticClass( ) ) )
	{
		// Decide whether this is a referenced asset pointer, or an inline-exported object.
		if( ( Property->PropertyFlags & CPF_AssetRegistrySearchable ) != 0 )
		{
			SerializePropertyAssetReference( JSONObjectValue, Cast< UObjectPropertyBase >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
		}
		else
		{
			// Inline-import based on class name.
			SerializePropertySubObject( JSONObjectValue, Cast< UObjectPropertyBase >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
		}
	}
	else if( Property->IsA( UStructProperty::StaticClass( ) )  )
	{
		// Contained struct.
		SerializePropertyStruct( JSONObjectValue, Cast< UStructProperty >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	}
	else if( Property->IsA( UArrayProperty::StaticClass( ) ) )
	{
		SerializePropertyArray( JSONObjectValue, Cast< UArrayProperty >( Property ), PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	}
	else
	{
		SerializePropertyString( JSONObjectValue, Property, PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	}
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyBool( TSharedPtr< FJsonValue >& JSONObjectValue, UBoolProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	FString valueString;
	Property->ExportTextItem( valueString, PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	if( valueString.Equals( TEXT( "True" ) ) && valueString.Equals( TEXT( "False" ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectSerialization] ERROR: Expecting boolean when serializing property to JSON (Property: %s, Value: %s). Aborting." ), *valueString, *Property->GetName( ) );
		return;
	}

	JSONObjectValue = MakeShareable( new FJsonValueBoolean( valueString == TEXT( "True" ) ) );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyByte( TSharedPtr< FJsonValue >& JSONObjectValue, UByteProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	FString valueString;

	Property->ExportTextItem( valueString, PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	JSONObjectValue = MakeShareable( new FJsonValueString( valueString ) );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyAssetReference( TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	FString valueString;

	// Serialize the name of the asset.
	Property->ExportTextItem( valueString, PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );
	JSONObjectValue = MakeShareable( new FJsonValueString( valueString ) );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertySubObject( TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	UObject* pObject = Property->GetObjectPropertyValue(PropertyValue);
	if( JSONObjectValue.IsValid( ) )
	{
		FJoyObjectSerialization::Serialize( JSONObjectValue, pObject->GetClass( ), ( uint8* )pObject, pObject->GetOuter( ), PPF_ExportsNotFullyQualified | PPF_Copy, true );
	}
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyStruct( TSharedPtr< FJsonValue >& JSONObjectValue, UStructProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	// Serialize Struct as JsonObject
	Serialize( JSONObjectValue, Property->Struct, PropertyValue, Parent, PortFlags, false );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyArray( TSharedPtr< FJsonValue >& JSONObjectValue, UArrayProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	FScriptArrayHelper arrayHelper( Property, PropertyValue );
	FScriptArrayHelper arrayHelperDefault( Property, DefaultValue );

	TArray< TSharedPtr< FJsonValue > > JSONObjectArray;
	UStructProperty* structureProperty = Cast< UStructProperty >( Property->Inner );
	uint8* structureDefaults = nullptr;

	if( structureProperty != nullptr )
	{
		checkSlow( structureProperty->Struct );
		structureDefaults = ( uint8* )FMemory::Malloc( structureProperty->Struct->GetStructureSize( ) );
		structureProperty->InitializeValue( structureDefaults );
	}

	int32 Count = 0;
	for( int32 i = 0; i<arrayHelper.Num( ); i++ )
	{
		uint8* PropData = arrayHelper.GetRawPtr( i );
		uint8* PropDefault = ( DefaultValue && arrayHelperDefault.Num( ) > i ) ? arrayHelperDefault.GetRawPtr( i ) : structureDefaults;

		// Do not re-export duplicate data from superclass when exporting to .int32 file
		if( Property->Inner->Identical(PropData, PropDefault) )
		{
			continue;
		}
		TSharedPtr< FJsonValue > InnerJSONObject;
		SerializeProperty( InnerJSONObject, Property->Inner, PropData, PropDefault, Parent, PortFlags, i, SerializeRootScope );
		if( InnerJSONObject.IsValid( ) )
		{
			JSONObjectArray.Add( InnerJSONObject );
		}
	}

	if( structureDefaults )
	{
		structureProperty->DestroyValue( structureDefaults );
		FMemory::Free( structureDefaults );
	}

	JSONObjectValue = MakeShareable( new FJsonValueArray(JSONObjectArray) );
}

//----------------------------------------------------------------------------------------------------
void FJoyObjectSerialization::SerializePropertyString( TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, const uint8* PropertyValue, const uint8* DefaultValue, UObject* Parent, int32 PortFlags, UObject* SerializeRootScope )
{
	FString valueString;
	Property->ExportTextItem( valueString, PropertyValue, DefaultValue, Parent, PortFlags, SerializeRootScope );

	JSONObjectValue = MakeShareable( new FJsonValueString( valueString ) );
}