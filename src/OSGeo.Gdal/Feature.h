#pragma once

#include <ogr_feature.h>

using namespace System;
using namespace System::Data;

namespace OSGeo
{
	namespace Ogr
	{
		ref class Geometry;

		public ref class Feature : public IDataRecord
		{
		private:
			Geometry^ _geometry;
			OGRFeature* _feature;
			~Feature();
			!Feature();
			array<unsigned char>^ GetBytes(int i);
		internal:
			Feature(OGRFeature* feature);
		public:
			property Geometry^ Geometry
			{
				OSGeo::Ogr::Geometry^ get();
			}

			property int FieldCount
			{
				virtual int get();
			}

			property Object^ Item[int]
			{
				virtual Object^ get(int i) = IDataRecord::default::get;
			}

			property Object^ Item[String^]
			{
				virtual Object^ get(String^ name) = IDataReader::default::get;
			}

			virtual bool GetBoolean(int i);

			virtual unsigned char GetByte(int i);

			virtual long long GetBytes(int i, long long fieldOffset, array<unsigned char>^ buffer, int bufferoffset, int length);

			virtual wchar_t GetChar(int i);

			virtual long long GetChars(int i, long long fieldoffset, array<wchar_t>^ buffer, int bufferoffset, int length);

			virtual IDataReader^ GetData(int i);

			virtual String^ GetDataTypeName(int i);

			virtual DateTime GetDateTime(int i);

			virtual Decimal GetDecimal(int i);

			virtual double GetDouble(int i);

			virtual Type^ GetFieldType(int i);

			virtual float GetFloat(int i);

			virtual Guid GetGuid(int i);

			virtual short GetInt16(int i);

			virtual int GetInt32(int i);

			virtual long long GetInt64(int i);

			virtual String^ GetName(int i);

			virtual int GetOrdinal(System::String^ name);

			/// <summary>Gets the string value of the specified field.</summary>
			/// <param name="i">The index of the field to find.</param>
			/// <returns>The string value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through FieldCount.</exception>
			virtual System::String^ GetString(int i);

			virtual Object^ GetValue(int i);

			virtual int GetValues(array<Object^>^ values);

			virtual bool IsDBNull(int i);
		};
	}
}