// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#pragma once

#include "SteelHuntersPCH.h"

#include "Object.h"
#include "ObjectMacros.h"

#include "Templates/SharedPointer.h"

#include "JsonObjectConverter.h"

#include "JoySerializationManager.generated.h"

// UJoySerializationManager Class Definition.
UCLASS( Transient )
class STEELHUNTERS_API UJoySerializationManager : public UObject
{
	GENERATED_BODY( )

private:
	const static FName JSONRootFolder;

public:
	/*
	 *	Object Deserialization.
	*/
	static bool LoadJSON( FString& JSONContentsOut, const FName& SubfolderName, const FName& Filename );
	static bool LoadJSON( FString& JSONContentsOut, const FName& FilePath );

	static bool DeserializeObjectFromFile( UObject* Object, const FName& SubfolderName, const FName& Filename, bool CreateFromObjectOnMissing = true, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool DeserializeObjectFromFile( UObject* Object, const FName& FilePath, bool CreateFromObjectOnMissing = true, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );

	static bool DeserializeObjectFromJson( UObject* Object, const TSharedPtr< class FJsonObject >& JSONObject, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool DeserializeObjectFromJsonString( UObject* Object, const FString& JSONString, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool DeserializeObjectDataFromJsonString( uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, const FString& JsonString, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );

	// Create a UObject from a json string.
	static bool CreateObjectFromJsonString( UObject*& Object, UObject* Parent, const FString& JsonString, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );

	/*
	 *	Object Serialization.
	*/

	static bool SaveJSON( const FString& JSONContents, const FName& SubfolderName, const FName& Filename );
	static bool SaveJSON( const FString& JSONContents, const FName& FilePath );

	// Serialize a UObject to JSON.
	static bool SerializeObjectToFile( const UObject* Object, const FName& SubfolderName, const FName& Filename, bool SerializeClassName, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool SerializeObjectToFile( const UObject* Object, const FName& FilePath, bool SerializeClassName, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );

	static bool SerializeObjectToJson( const UObject* Object, TSharedPtr< class FJsonValue >& JSONObjectValue, bool SerializeClassName, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool SerializeObjectToJsonString( const UObject* Object, FString& JSONString, bool SerializeClassName, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );
	static bool SerializeObjectDataToJsonString( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, FString& JSONString, bool SerializeClassName, int32 PortFlags = PPF_ExportsNotFullyQualified | PPF_Copy );

	static bool SerializeJsonObjectToString( TSharedPtr< FJsonObject >& JSONObject, FString& JSONString );

	/*
	 *	Utilities.
	*/

	// Get the root folder for all JSON files (most JSON is stored in various subfolders).
	static const FName GetJSONRootFolder( );

	// Build the full JSON file path (do *not* include the extension in the file name).
	static FString BuildJSONPath( const FName& SubfolderName, const FName& Filename );

	static bool CheckFileExists( const FName& SubfolderName, const FName& Filename );
	static bool CheckFileExists( const FName& FilePath );

	/*
	 *	Structure serializaiton/deserialization templated method definitions.
	*/

	// Structure serialization method definitions.
	template< typename T >
	static bool SerializeStructToFile( const T& StructInstance, const FName& SubfolderName, const FName& Filename )
	{
		FName filePath = *BuildJSONPath( SubfolderName, Filename );
		return( SerializeStructToFile< T >( StructInstance, filePath ) );
	}

	template< typename T >
	static bool SerializeStructToFile( const T& StructInstance, const FName& FilePath )
	{
		FString json;
		if( !FJsonObjectConverter::UStructToJsonObjectString< T >( StructInstance, json ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to serialize passed-in UStruct to JSON string (%s)." ), *FilePath.ToString( ) );
			return false;
		}

		// Save the JSON string to a file. Hopefully.
		if( !SaveJSON( json, FilePath ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to save file from JSON during UStruct serialization (%s)." ), *FilePath.ToString( ) );
			return false;
		}

		return true;
	}

	// Structure deserialization methods definitions.
	template< typename T >
	static bool DeserializeStructFromFile( T* StructType, const FName& SubfolderName, const FName& Filename )
	{
		FName filePath = *BuildJSONPath( SubfolderName, Filename );
		return( DeserializeStructFromFile< T >( StructType, filePath ) );
	}

	template< typename T >
	static bool DeserializeStructFromFile( T* StructInstance, const FName& FilePath )
	{
		if( !CheckFileExists( FilePath ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: File intended for deserialization does not exist (%s)." ), *FilePath.ToString( ) );
			return false;
		}

		// Save the JSON string to a file. Hopefully.
		FString json;
		if( !LoadJSON( json, FilePath ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to load JSON during deserialization for UStruct (%s)." ), *FilePath.ToString( ) );
			return false;
		}

		if( !FJsonObjectConverter::JsonObjectStringToUStruct< T >( json, StructInstance, 0, 0 ) )
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to deserialize UStruct from JSON string (%s)." ), *FilePath.ToString( ) );
			return false;
		}


		return true;
	}
};