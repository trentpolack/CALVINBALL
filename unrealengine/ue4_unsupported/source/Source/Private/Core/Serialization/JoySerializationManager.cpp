// Copyright 2015-2018 Joy Machine, LLC. All rights reserved.

#include "JoySerializationManager.h"

#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

#include "JoyObjectDeserialization.h"
#include "JoyObjectSerialization.h"

// Static Definitions (class-scope).
const FName UJoySerializationManager::JSONRootFolder = TEXT( "json" );

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::LoadJSON( FString& JSONContentsOut, const FName& SubfolderName, const FName& Filename )
{
	FName filePath = *BuildJSONPath( SubfolderName, Filename );
	return( LoadJSON( JSONContentsOut, filePath ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::LoadJSON( FString& JSONContentsOut, const FName& FilePath )
{
	if( !CheckFileExists( FilePath ) )
	{
		// File doesn't exist yet.
		return false;
	}

	// Build the path to the file and load it into the passed-in string.
	if( !FFileHelper::LoadFileToString( JSONContentsOut, *FilePath.ToString( ), FFileHelper::EHashOptions::EnableVerify ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to load JSON (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	UE_LOG( SteelHuntersLog, VeryVerbose, TEXT( "[UJoySerializationManager] Loaded JSON (%s)." ), *FilePath.ToString( ) );
	return true;
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::DeserializeObjectFromFile( UObject* Object, const FName& SubfolderName, const FName& Filename, bool CreateFromObjectOnMissing, int32 PortFlags )
{
	FName filePath = *BuildJSONPath( SubfolderName, Filename );
	return( DeserializeObjectFromFile( Object, filePath, CreateFromObjectOnMissing, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::DeserializeObjectFromFile( UObject* Object, const FName& FilePath, bool CreateFromObjectOnMissing, int32 PortFlags )
{
	if( !IsValid( Object ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Invalid object pointer passed in during deserialization from file (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	// Load the JSON string from the file. Hopefully.
	FString json;
	if( !LoadJSON( json, FilePath ) )
	{
		if( CreateFromObjectOnMissing )
		{
			if( !SerializeObjectToFile( Object, FilePath, true ) )
			{
				UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: On failed deserialization from file, serialization to file -- to create it -- also failed (%s)." ), *FilePath.ToString( ) );
				return false;
			}

			// Now deserialize the object.
			//	NOTE (trent, 6/6/17): Could just return the object as-is, but this at least ensures the serialized data is valid.
			if( !LoadJSON( json, FilePath ) )
			{
				UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: On failed deserialization from file, serialization to file succeed, but that file's JSON failed (%s)." ), *FilePath.ToString( ) );
				return false;
			}
		}
		else
		{
			UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to load JSON from file during object deserialization (%s)." ), *FilePath.ToString( ) );
			return false;
		}
	}

	// Deserialize the object data from the loaded JSON string.
	if( !DeserializeObjectFromJsonString( Object, json, PortFlags ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to deserialize object from file (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::DeserializeObjectFromJsonString( UObject* Object, const FString& JsonString, int32 PortFlags )
{
	uint8* ObjectData = ( uint8* )Object;
	return( FJoyObjectDeserialization::DeserializeDataFromJsonString( ObjectData, Object->GetClass( ), Object->GetOuter( ), JsonString, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::DeserializeObjectFromJson( UObject* Object, const TSharedPtr< FJsonObject >& JSONObject, int32 PortFlags )
{
	uint8* ObjectData = ( uint8* )Object;
	return( FJoyObjectDeserialization::DeserializeDataFromJson( ObjectData, Object->GetClass( ), Object->GetOuter( ), JSONObject, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::DeserializeObjectDataFromJsonString( uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, const FString& JsonString, int32 PortFlags )
{
	return( FJoyObjectDeserialization::DeserializeDataFromJsonString( ObjectData, ObjectClass, Parent, JsonString, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::CreateObjectFromJsonString( UObject*& Object, UObject* Parent, const FString& JsonString, int32 PortFlags )
{
	return( FJoyObjectDeserialization::DeserializeDataFromJsonString( (uint8*&)Object, nullptr, Parent, JsonString, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SaveJSON( const FString& JSONContents, const FName& SubfolderName, const FName& Filename )
{
	FName filePath = *BuildJSONPath( SubfolderName, Filename );
	return( SaveJSON( JSONContents, filePath ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SaveJSON( const FString& JSONContents, const FName& FilePath )
{
	// Take a pre-populated JSON string and save it out to a file.
	if( !FFileHelper::SaveStringToFile( JSONContents, *FilePath.ToString( ), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get( ), EFileWrite::FILEWRITE_None ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to load JSON (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	UE_LOG( SteelHuntersLog, VeryVerbose, TEXT( "[UJoySerializationManager] Loaded JSON (%s)." ), *FilePath.ToString( ) );
	return true;
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeObjectToFile( const UObject* Object, const FName& SubfolderName, const FName& Filename, bool SerializeClassName, int32 PortFlags )
{
	FName filePath = *BuildJSONPath( SubfolderName, Filename );
	return( SerializeObjectToFile( Object, filePath, SerializeClassName, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeObjectToFile( const UObject* Object, const FName& FilePath, bool SerializeClassName, int32 PortFlags )
{
	if( !IsValid( Object ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Invalid object pointer passed in during serialization to file (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	// Sserialize the object data into a JSON string.
	FString json;
	if( !SerializeObjectToJsonString( Object, json, SerializeClassName, PortFlags ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to serialize object to file (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	// Save the JSON string to a file. Hopefully.
	if( !SaveJSON( json, FilePath ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Failed to save file from JSON during object serialization (%s)." ), *FilePath.ToString( ) );
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeObjectToJson( const UObject* Object, TSharedPtr< FJsonValue >& JSONObjectValue, bool SerializeClassName, int32 PortFlags )
{
	if( !Object )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Invalid object data (nullptr) trying to be serialized to JSON. Aborting." ) );
		return false;
	}

	return( FJoyObjectSerialization::SerializeDataToJson( ( uint8* )Object, Object->GetClass( ), Object->GetOuter( ), JSONObjectValue, SerializeClassName, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeObjectToJsonString( const UObject* Object, FString& JSONString, bool SerializeClassName, int32 PortFlags )
{
	if( !IsValid( Object ) )
	{
		UE_LOG( SteelHuntersLog, Error, TEXT( "[UJoySerializationManager] ERROR: Invalid object data (nullptr) trying to be serialized to JSON string. Aborting." ) );
		return false;
	}

	return( FJoyObjectSerialization::SerializeDataToJsonString( ( uint8* )Object, Object->GetClass( ), Object->GetOuter( ), JSONString, SerializeClassName, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeJsonObjectToString( TSharedPtr< FJsonObject >& JSONObject, FString& JSONString )
{
	JSONString.Empty( );

	TSharedRef< TJsonWriter< > > writer = TJsonWriterFactory< >::Create( &JSONString );
	return( FJsonSerializer::Serialize( JSONObject.ToSharedRef( ), writer ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::SerializeObjectDataToJsonString( const uint8* ObjectData, UStruct* ObjectClass, UObject* Parent, FString& JSONString, bool SerializeClassName, int32 PortFlags )
{
	return( FJoyObjectSerialization::SerializeDataToJsonString( ObjectData, ObjectClass, Parent, JSONString, SerializeClassName, PortFlags ) );
}

//----------------------------------------------------------------------------------------------------
const FName UJoySerializationManager::GetJSONRootFolder( )
{
	return JSONRootFolder;
}

//----------------------------------------------------------------------------------------------------
FString UJoySerializationManager::BuildJSONPath( const FName& SubfolderName, const FName& Filename )
{
	return( FString::Printf( TEXT( "%s%s/%s/%s.json" ), *FPaths::ProjectDir( ), *GetJSONRootFolder( ).ToString( ), *SubfolderName.ToString( ), *Filename.ToString( ) ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::CheckFileExists( const FName& SubfolderName, const FName& Filename )
{
	return( CheckFileExists( *BuildJSONPath( SubfolderName, Filename ) ) );
}

//----------------------------------------------------------------------------------------------------
bool UJoySerializationManager::CheckFileExists( const FName& FilePath )
{
	return( FPaths::FileExists( FilePath.ToString( ) ) );
}

// This is probably necessary. Maybe not. 
#ifdef ENUMERATE_PROPERTY_TYPES
	#undef ENUMERATE_PROPERTY_TYPES
#endif
