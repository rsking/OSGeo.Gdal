#pragma once

#include <ogr_feature.h>

using namespace System;
using namespace System::Data;

namespace OSGeo
{
	namespace Ogr
	{
		ref class Geometry;
		ref class FeatureDefinition;

		/// <summary>Represents a OGR Feature.</summary>
		public ref class Feature sealed : public IDataRecord
		{
		private:
			/// <summary>The geometry.</summary>
			Geometry^ _geometry;
			
			/// <summary>The OGR feature.</summary>
			OGRFeature* _feature;
			
			/// <summary>Disposes this instance.</summary>
			~Feature();
			
			/// <summary>Finalises this instance.</summary>
			!Feature();

			/// <summary>Gets the bytes from the specified column.</summary>
			array<unsigned char>^ GetBytes(int i);
		internal:
			/// <summary>Gets the feature handle.</summary>
			property OGRFeature* Handle
			{
				OGRFeature* get()
				{
					return this->_feature;
				}
			}

			/// <summary>Initialises a new instance of the <see cref="Feature"/> class from the specified <see cref="OGRFeature"/>.</summary>
			/// <param name="feature">The OGR Feature.</param>
			Feature(OGRFeature* feature);
		public:
			/// <summary>Initialises a new instance of the <see cref="Feature"/> class with the specified <see cref="FeatureDefinition"/>.</summary>
			/// <param name="featureDefinition">The feature definition.</param>
			Feature(FeatureDefinition^ featureDefinition);

			/// <summary>Gets the geometry associated with this instance.</summary>
			property Geometry^ Geometry
			{
				OSGeo::Ogr::Geometry^ get();
				void set(OSGeo::Ogr::Geometry^ geometry);
			}
			
			/// <summary>Gets the number of columns in the current feature.</summary>
			property int FieldCount
			{
				virtual int get();
			}
			
			/// <summary>Gets or sets the FID.</summary>
			property long Fid
			{
				long get();
				void set(long value);
			}
			
			/// <summary>Gets or sets the column located at the specified index.</summary>
			property Object^ Item[int]
			{
				virtual Object^ get(int i) = IDataRecord::default::get;
				void set(int i, Object^ value);
			}
			
			/// <summary>Gets or sets the column with the specified name.</summary>
			property Object^ Item[String^]
			{
				virtual Object^ get(String^ name) = IDataReader::default::get;
				void set(String^ name, Object^ value);
			}
			
			/// <summary>Gets the value of the specified column as a <see cref="Boolean"/>.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The value of the column.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual bool GetBoolean(int i);
			
			/// <summary>Gets the 8-bit unsigned integer value of the specified column.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The 8-bit unsigned integer value of the specified column.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual unsigned char GetByte(int i);
			
			/// <summary>Reads a stream of bytes  offset into the buffer as an array, starting at the given buffer offset.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <param name="fieldOffset">The index within the field from which to start the read operation.</param>
			/// <param name="buffer">The buffer into which to read the stream of bytes.</param>
			/// <param name="bufferoffset">The index for <paramref name="buffer"/> to start the read operation.</param>
			/// <param name="length">The number of bytes to read.</param>
			/// <returns>The actual number of bytes read.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual long long GetBytes(int i, long long fieldOffset, array<unsigned char>^ buffer, int bufferoffset, int length);
			
			/// <summary>Gets the character value of the specified column.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The character value of the specified column.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual wchar_t GetChar(int i);
			
			/// <summary>Reads a stream of characters from the specified column offset into the buffer as an array, starting at the given buffer offset.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <param name="fieldoffset">The index within the field from which to start the read operation.</param>
			/// <param name="buffer">The buffer into which to read the stream of bytes.</param>
			/// <param name="bufferoffset">The index for <paramref name="buffer"/> to start the read operation.</param>
			/// <param name="length">The number of bytes to read.</param>
			/// <returns>The actual number of characters read.</returns>	
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual long long GetChars(int i, long long fieldoffset, array<wchar_t>^ buffer, int bufferoffset, int length);
			
			/// <summary>Returns an <see cref="IDataReader"/> for the specified column ordinal.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The <see cref="IDataReader"/> for the specified column ordinal.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual IDataReader^ GetData(int i);
			
			/// <summary>Gets the data type information for the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The data type information for the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual String^ GetDataTypeName(int i);
			
			/// <summary>Gets the date and time data value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The date and time data value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual DateTime GetDateTime(int i);
			
			/// <summary>Gets the fixed-position numeric value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The  fixed-position numeric value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual Decimal GetDecimal(int i);
			
			/// <summary>Gets the double-precision floating point number of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The double-precision floating point number of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual double GetDouble(int i);
			
			/// <summary>Gets the <see cref="Type"/> information corresponding to the type of <see cref="Object"/> that would be returned from <see cref="GetValue"/>.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The <see cref="Type"/> information corresponding to the type of <see cref="Object"/> that would be returned from <see cref="GetValue"/>.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual Type^ GetFieldType(int i);
			
			/// <summary>Gets the single-precision floating point number of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The single-precision floating point number of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual float GetFloat(int i);
			
			/// <summary>Returns the GUID value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The GUID value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual Guid GetGuid(int i);
			
			/// <summary>Gets the 16-bit signed integer value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The 16-bit signed integer value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual short GetInt16(int i);
			
			/// <summary>Gets the 32-bit signed integer value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The 32-bit signed integer value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual int GetInt32(int i);
			
			/// <summary>Gets the 64-bit signed integer value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The 64-bit signed integer value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual long long GetInt64(int i);
			
			/// <summary>Gets the name for the field to find.</summary>
			/// <param name="i">The index of the field to find.</param>
			/// <returns>The name of the field or the empty string (""), if there is no value to return.</returns>
			virtual String^ GetName(int i);
			
			/// <summary>Return the index of the named field.</summary>
			/// <param name="name">The name of the field to find.</param>
			/// <returns>The index of the named field.</returns>
			virtual int GetOrdinal(System::String^ name);
			
			/// <summary>Gets the string value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The string value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual System::String^ GetString(int i);
			
			/// <summary>Return the value of the specified field.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns>The <see cref="Object"/> value of the specified field.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual Object^ GetValue(int i);
			
			/// <summary>Populates an array of objects with the column values of the current record.</summary>
			/// <param name="values">An array of <see cref="Object"/> to copy the attribute fields into.</param>
			/// <returns>The number of instances of <see cref="Object"/> in the array.</returns>
			virtual int GetValues(array<Object^>^ values);
			
			/// <summary>Return whether the specified field is set to null.</summary>
			/// <param name="i">The zero-based column ordinal.</param>
			/// <returns><see langword="true"/> if the specified field is set to null; otherwise, <see langword="false"/>.</returns>
			/// <exception cref="System::IndexOutOfRangeException">The index passed was outside the range of 0 through <see cref="FieldCount"/>.</exception>
			virtual bool IsDBNull(int i);
		};
	}
}