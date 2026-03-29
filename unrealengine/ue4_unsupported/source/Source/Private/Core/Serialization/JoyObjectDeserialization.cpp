// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#include "JoyObjectDeserialization.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "JoySerializationInternal.h"

/*
*	IJoySerializeValueProperty Interface Definition.
*/
class IJoyDeserializeValueProperty
{
protected:
	virtual void CopyData( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, uint8* DestinationData ) const = 0;

public:
	virtual bool SetProperty( UProperty* Property ) const = 0;

	bool DeserializeProperty( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText = ( FOutputDevice* )GError ) const
	{
		if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::Number ) ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[IJoyDeserializeValueProperty] ERROR: Expected number while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
			return false;
		}

		CopyData( JSONObjectValue, Property, Data );
		return true;
	}
};

/*
 *	Value Property Deserialization class definition (I hate doing this in a CPP file).
*/
template < typename T >
class FJoyDeserializeValueProperty : public IJoyDeserializeValueProperty
{
protected:
	typedef typename FJoyValuePropertyType< T >::PropertyType PropertyType;

protected:
	virtual void CopyData( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, uint8* DestinationData ) const override
	{
		T sourceData = static_cast< T >( JSONObjectValue->AsNumber( ) );

		Property->CopySingleValue( DestinationData, &sourceData );
	}

public:
	bool SetProperty( UProperty* Property ) const override
	{
		return( Property->IsA( PropertyType::StaticClass( ) ) );
	}
};

//----------------------------------------------------------------------------------------------------
FJoyObjectDeserialization::FJoyObjectDeserialization( )
{	}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializeDataFromJson( uint8*& ObjectData, UStruct* ObjectClass, UObject* Parent, const TSharedPtr< FJsonObject >& JSONObject, int32 PortFlags )
{
	if( !JSONObject.IsValid( ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid JSON object during deserialization. Aborting." ) );
		return false;
	}

	if( ObjectData )
	{
		// Create the object from Json
		const TSharedPtr< FJsonValue >* pClassValue = JSONObject->Values.Find(TEXT("Class" ) );
		if( !( pClassValue && pClassValue->IsValid( ) && ( *pClassValue )->Type == EJson::String) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid JSON object data during deserialization. Aborting." ) );
			return false;
		}

		FString classNameString = ( *pClassValue )->AsString( );
		UObject* pClassObject = StaticFindObject( UClass::StaticClass( ), ANY_PACKAGE, *classNameString );
		if( !pClassObject )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid JSON class name (%s) during deserialization. Aborting." ), *classNameString );
			return false;
		}

		UClass* pClassThis = Cast< UClass >( pClassObject );
		if( !pClassThis )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid JSON class name (%s) during deserialization of a property (%s). Aborting." ), *classNameString, *pClassObject->GetName( ) );
			return false;
		}

		UObject* pCreatedObject = NewObject< UObject >( Parent, FName( NAME_None ) );
		if( !pCreatedObject )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Unable to create new object during deserialization (Parent: %s). Aborting." ), ( IsValid( Parent ) ? ( *Parent->GetName( ) ) : TEXT( "Unknown" ) ) );
			return false;
		}

		ObjectData = ( uint8* )pCreatedObject;
		ObjectClass = pClassThis;
	}

	if( !ObjectClass )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid UObject class during deserializaiton. Aborting." ) );
		return false;
	}

	return( Deserialize( ObjectData, ObjectClass, JSONObject, Parent, PortFlags, ( FOutputDevice* )GError ) );
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializeDataFromJsonString( uint8*& ObjectData, UStruct* ObjectClass, UObject* Parent, const FString& JSONString, int32 PortFlags )
{
	TSharedPtr< FJsonObject > pJSONObject;
	TSharedRef< TJsonReader< > > JSONReader = TJsonReaderFactory< >::Create( JSONString );
	FString errorString;

	if( !FJsonSerializer::Deserialize( JSONReader, pJSONObject ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Error deserializing JSON string: %s. Aborting." ), *JSONReader->GetErrorMessage( ) );
		return false;
	}

	return( DeserializeDataFromJson( ObjectData, ObjectClass, Parent, pJSONObject, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::Deserialize( uint8* ObjectData, UStruct* ObjectClass, const TSharedPtr< FJsonObject >& JSONObject, UObject* Parent, int32 PortFlags, FOutputDevice* ErrorText )
{
	bool success = true;

	// Read the UStruct's properties one by one.
	for( UProperty* pProperty = ObjectClass->PropertyLink; pProperty; pProperty = pProperty->PropertyLinkNext )
	{
		if( pProperty->ShouldPort( PortFlags ) )
		{
			if( !pProperty->ValidateImportFlags( PortFlags, ErrorText ) )
			{
				UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid input tag for JSON deserialization (Property: %s). Aborting." ), *pProperty->GetName( ) );
	
				success = false;
				break;
			}

			const TSharedPtr< FJsonValue >* pJSONObjectValue = JSONObject->Values.Find( pProperty->GetName( ) );
			if( !pJSONObjectValue )
			{
				// Property isn't in the JSON, just use a default.
				continue;
			}

			if( !DeserializeProperty( *pJSONObjectValue, pProperty, pProperty->ContainerPtrToValuePtr< uint8 >( ObjectData ), Parent, PortFlags, -1, ErrorText ) )
			{
				success = false;
				break;
			}
		}
	}
	return success;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializeProperty( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, uint8* PropertyValue, UObject* Parent, int32 PortFlags, int32 ArrayIndex, FOutputDevice* ErrorText )
{
	bool success = true;

	// Static list of value property converters.
#define STATIC_JSON_CONVERTER( CppType, UEType ) \
	static const FJoyDeserializeValueProperty< CppType > JSONValueDeserializer_##UEType;

ENUMERATE_PROPERTY_TYPES( STATIC_JSON_CONVERTER )

#undef STATIC_JSON_CONVERTER

#define STATIC_JSON_CONVERTER_ELEMENT( CppType, UEType ) &JSONValueDeserializer_##UEType,

	// A corresponding static list of converter base class pointers
	static const IJoyDeserializeValueProperty* JSONValueDeserializers[] =
	{
		ENUMERATE_PROPERTY_TYPES( STATIC_JSON_CONVERTER_ELEMENT )
	};

#undef STATIC_JSON_CONVERTER_ELEMENT

	// Handle number properties.
	static const uint32 deserializerCount = sizeof( JSONValueDeserializers )/sizeof( JSONValueDeserializers[0] );
	bool handled = false;
	for ( uint32 i=0 ; i < deserializerCount ; ++i )
	{
		const IJoyDeserializeValueProperty* converter = JSONValueDeserializers[i];
		if( converter->SetProperty( Property ) )
		{
			success = converter->DeserializeProperty( JSONObjectValue, Property, PropertyValue, PortFlags, Parent, ErrorText );
			handled = true;
			break;
		}
	}

	if( handled )
	{
		// Welp, nailed it. Mic drop.
		return success;
	}

	// Handle non-numerical properties.
	if( Property->IsA( UByteProperty::StaticClass( ) ) )
	{
		success = DeserializePropertyByte( JSONObjectValue, Cast< UByteProperty >( Property ), PropertyValue, PortFlags, Parent, ErrorText );	
	}
	else if( Property->IsA( UBoolProperty::StaticClass( ) ) )
	{
		success = DeserializePropertyBool( JSONObjectValue, Cast< UBoolProperty >( Property ), PropertyValue, PortFlags, Parent, ErrorText );	
	}
	else if( Property->IsA( UObjectPropertyBase::StaticClass( ) )  )
	{
		// Decide whether this is a referenced asset pointer, or an inline-exported object.
		if( ( Property->PropertyFlags & CPF_AssetRegistrySearchable ) != 0 )
		{
			// Referenced asset.
			success = DeserializePropertyAssetReference( JSONObjectValue, Cast< UObjectPropertyBase>( Property ), PropertyValue, PortFlags, Parent, ErrorText );
		}
		else
		{
			// Inline-import based on class name.
			success = DeserializePropertySubObject( JSONObjectValue, Cast< UObjectPropertyBase>( Property ), PropertyValue, PortFlags, Parent, ErrorText );
		}
	}
	else if( Property->IsA( UStructProperty::StaticClass( ) )  )
	{
		// Contained struct.
		success = DeserializePropertyStruct( JSONObjectValue, Cast< UStructProperty >( Property ), PropertyValue, PortFlags, Parent, ErrorText );
	}
	else if( Property->IsA( UArrayProperty::StaticClass( ) ) )
	{
		success = DeserializePropertyArray( JSONObjectValue, Cast< UArrayProperty >( Property ), PropertyValue, PortFlags, Parent, ErrorText );	
	}
	else
	{
		success = DeserializePropertyString( JSONObjectValue, Property, PropertyValue, PortFlags, Parent, ErrorText );		
	}

	return success;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyByte( const TSharedPtr<class FJsonValue>& JSONObjectValue, UByteProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::String ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected an enumeration string while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	if( !Property->Enum )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected an enumeration declaration while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	FString EnumString = JSONObjectValue->AsString( );
	const int32 EnumIndex = Property->Enum->GetIndexByName( *EnumString );
	if( EnumIndex == INDEX_NONE )
	{
		// Unknown value.
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Unknown enumeration value while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
	}
	*( uint8* )Data = EnumIndex;

	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyBool( const TSharedPtr< FJsonValue >& JSONObjectValue, UBoolProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::Boolean ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected a boolean property while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	bool src = JSONObjectValue->AsBool( );
	Property->CopySingleValue( Data, &src );

	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyAssetReference( const TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::String ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected an asset reference while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	FString assetNameString = JSONObjectValue->AsString( );
	if( assetNameString.IsEmpty( ) )
	{
		Property->SetObjectPropertyValue( Data, nullptr );
	}
	else
	{
		UObject* pAssetObject = StaticFindObject( Property->PropertyClass, ANY_PACKAGE, *assetNameString );
		if( !pAssetObject )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Could not find asset while deserializing (Property: %s, Asset: %s). Aborting." ), *Property->GetName( ), *assetNameString );
			return false;
		}

		if( !pAssetObject->IsA( Property->PropertyClass ) )
		{
			// Wrong class of asset.
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Wrong class name for asset while deserializing (Property: %s, Asset: %s). Aborting." ), *Property->GetName( ), *assetNameString );
			return false;
		}

		Property->SetObjectPropertyValue( Data, pAssetObject );
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertySubObject( const TSharedPtr< FJsonValue >& JSONObjectValue, UObjectPropertyBase* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	if( !( JSONObjectValue.IsValid( ) && ( ( JSONObjectValue->Type == EJson::Object ) || ( JSONObjectValue->Type == EJson::String ) ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected string (null) or class-object pair while deserializing subobject (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	if( JSONObjectValue->Type == EJson::String )
	{
		// Better be the string "null".
		FString valueString = JSONObjectValue->AsString( );
		if( !valueString.Equals( "null" ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected a \"null\" string, instead got: \"%s\". Occured while deserializing class-object pair while deserializing subobject (Property: %s). Aborting." ), *valueString, *Property->GetName( ) );
			return false;
		}

		Property->SetObjectPropertyValue( Data, nullptr );
		return true;
	}

	TSharedPtr< FJsonObject > JSONObjectSpec = JSONObjectValue->AsObject( );
	if( !JSONObjectValue.IsValid( ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid class-object pair while deserializing subobject (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	const TSharedPtr< FJsonValue >* pClassValue = JSONObjectSpec->Values.Find(TEXT("Class" ) );
	if( !(pClassValue && pClassValue->IsValid( ) && ( *pClassValue )->Type == EJson::String) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Could not find class name while deserializing subobject (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	FString classNameString = ( *pClassValue )->AsString( );
	UObject* pClassObject = StaticFindObject( UClass::StaticClass( ), ANY_PACKAGE, *classNameString );
	if( !pClassObject )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid class name while deserializing subobject (Property: %s, Class Name: %s). Aborting." ), *Property->GetName( ), *classNameString );
		return false;
	}

	UClass* ObjectClass = Cast< UClass >( pClassObject );
	if( !ObjectClass )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid class name while deserializing subobject (Property: %s, Class Name: %s). Object should be a class. Aborting." ), *Property->GetName( ), *classNameString );
		return false;
	}

	if( !ObjectClass->IsChildOf(Property->PropertyClass) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid class name for subobject during deserialization (Property: %s, Class Name: %s). Class should be: %s (or a subclass). Aborting." ), *Property->GetName( ), *classNameString, *Property->PropertyClass->GetName( ) );
		return false;
	}

	// Get the object archetype.
	TSharedPtr< FJsonObject > pJSONObject = JSONObjectSpec;	
	const TSharedPtr< FJsonValue >* pObjectValue = JSONObjectSpec->Values.Find( TEXT( "Object" ) );

	// The subobject is a child of the object. Hence. You know. Sub. Object.
	if( pObjectValue && pObjectValue->IsValid( ) )
	{
		if( ( *pObjectValue )->Type != EJson::Object )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Could not find object value while deserializing subobject (Property: %s). Aborting." ), *Property->GetName( ) );
			return false;
		}

		pJSONObject = ( *pObjectValue )->AsObject( );
	}		

	// Create the object finally.
	UObject* pObjectInstance = NewObject< UObject >( Parent, FName( NAME_None ), RF_Transactional );
	if( !Deserialize( ( uint8* )pObjectInstance, ObjectClass, pJSONObject, Parent, PortFlags, ErrorText) )
	{
		return false;
	}

	// The time. It has finally come.
	Property->SetObjectPropertyValue( Data, pObjectInstance );
	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyStruct( const TSharedPtr< FJsonValue >& JSONObjectValue, UStructProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText)
{
	checkSlow( Property->Struct );
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::Object ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Object not provided for deserializing a struct (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	// Get the struct object and deserialize its contents. 
	return( Deserialize( Data, Property->Struct, JSONObjectValue->AsObject( ), Parent, PortFlags, ErrorText ) );
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyArray( const TSharedPtr< FJsonValue >& JSONObjectValue, UArrayProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	checkSlow( Property->Inner );
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::Array ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected an array type while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}
	const TArray< TSharedPtr< FJsonValue > > ArrayJSONObject = JSONObjectValue->AsArray( );

	FScriptArrayHelper arrayHelper( Property, Data );
	for (int32 i = 0; i < ArrayJSONObject.Num( ); ++i)
	{
		const TSharedPtr< FJsonValue >& InnerValue = ArrayJSONObject[i];
		if( !InnerValue.IsValid( ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Invalid array element encountered while deserializing (Property: %s, Array Index: %d). Aborting." ), *Property->GetName( ), i );
			return false;
		}

		// Expand the array to ensure tah this index is valid.
		arrayHelper.ExpandForIndex( i );		
		DeserializeProperty( InnerValue, Property->Inner, arrayHelper.GetRawPtr( i ), Parent, PortFlags, i, ErrorText );
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
bool FJoyObjectDeserialization::DeserializePropertyString( const TSharedPtr< FJsonValue >& JSONObjectValue, UProperty* Property, uint8* Data, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText )
{
	if( !( JSONObjectValue.IsValid( ) && ( JSONObjectValue->Type == EJson::String ) ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[FJoyObjectDeserialization] ERROR: Expected string while deserializing (Property: %s). Aborting." ), *Property->GetName( ) );
		return false;
	}

	Property->ImportText( *JSONObjectValue->AsString( ), Data, PortFlags, Parent, ErrorText );
	return true;
}