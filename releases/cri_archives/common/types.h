
#ifndef TYPES_H
#define TYPES_H

typedef char bool;
typedef char s8;
typedef uchar u8;
typedef int16 s16;
typedef uint16 u16;
typedef int16 s16;
typedef int32 s32;
typedef uint32 u32;
typedef int64 s64;
typedef uint64 u64;
typedef hfloat f16;
typedef float f32;
typedef double f64;

typedef struct
{
    f32 X;
    f32 Y;
} Vector2 <read=Vector2ToString>;

string Vector2ToString( Vector2& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f]", value.X, value.Y );

    return buffer;
}

typedef Vector2 TVector2;

typedef struct
{
    f16 X;
    f16 Y;
} Vector2Half <read=Vector2HalfToString>;

string Vector2HalfToString( Vector2Half& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f]", value.X, value.Y );

    return buffer;
}

typedef Vector2Half TVector2Half;

typedef struct
{
    f32 X;
    f32 Y;
    f32 Z;
} Vector3 <read=Vector3ToString>;

string Vector3ToString( Vector3& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f]", value.X, value.Y, value.Z );

    return buffer;
}

typedef Vector3 TVector3;

typedef struct
{
    f32 X;
    f32 Y;
    f32 Z;
	f32 W;
} Vector4 <read=Vector4ToString>;

string Vector4ToString( Vector4& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f, %.6f]", value.X, value.Y, value.Z, value.W );

    return buffer;
}

typedef Vector4 TVector4;
typedef TVector4 TQuaternion;

typedef struct
{
	Vector3 Min;
	Vector3 Max;
} BoundingBox <read=BoundingBoxToString>;

string BoundingBoxToString( BoundingBox& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f] [%.6f, %.6f, %.6f]", value.Min.X, value.Min.Y, value.Min.Z, value.Max.X, value.Max.Y, value.Max.Z );

    return buffer;
}

typedef BoundingBox TBoundingBox;

typedef struct
{
	Vector3 Center;
	f32 Radius;
} BoundingSphere <read=BoundingSphereToString>;

string BoundingSphereToString( BoundingSphere& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f] %.6f]", value.Center.X, value.Center.Y, value.Center.Z, value.Radius );

    return buffer;
}

typedef BoundingSphere TBoundingSphere;

typedef struct
{
	u32 Value;
} Normal11_11_11 <read=ReadNormal11_11_10>;

string ReadNormal11_11_10( Normal11_11_11& value )
{
	const int FULL_WIDTH = 32;
	
	const int X_POS = 0;
	const int X_WIDTH = 11;
	const int X_LSHIFT = FULL_WIDTH - X_POS - X_WIDTH;
	const int X_RSHIFT = FULL_WIDTH - X_WIDTH;
	const int X_DOT = (1 << (X_WIDTH - 1)) - 1;
	
	const int Y_POS = X_POS + X_WIDTH;
	const int Y_WIDTH = 11;
	const int Y_LSHIFT = FULL_WIDTH - Y_POS - Y_WIDTH;
	const int Y_RSHIFT = FULL_WIDTH - Y_WIDTH;
	const int Y_DOT = (1 << (Y_WIDTH - 1)) - 1;
	
	const int Z_POS = Y_POS + Y_WIDTH;
	const int Z_WIDTH = 10;	
	const int Z_LSHIFT = FULL_WIDTH - Z_POS - Z_WIDTH;
	const int Z_RSHIFT = FULL_WIDTH - Z_WIDTH;
	const int Z_DOT = (1 << (Z_WIDTH - 1)) - 1;
	
	u32 packed = value.Value;

	int xInt = ((int)(packed << X_LSHIFT)) >> X_RSHIFT;
	int yInt = ((int)(packed << Y_LSHIFT)) >> Y_RSHIFT;
	int zInt = ((int)(packed << Z_LSHIFT)) >> Z_RSHIFT;

	f32 x = (float)xInt / (float)X_DOT;
	f32 y = (float)yInt / (float)Y_DOT;
	f32 z = (float)zInt / (float)Z_DOT;
	
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f]", x, y, z );

	return buffer;
}

typedef Normal11_11_11 TNormal11_11_11;

typedef struct( u32 base )
{
	u32 Offset;
	
	if ( Offset != 0 )
	{
		local u32 returnPos = FTell();
		FSeek( base + Offset );
		string Value;
		FSeek( returnPos );
	}
} TStringOffset <read=StringOffsetToString>;

string StringOffsetToString( TStringOffset& value )
{
	if ( value.Offset == 0 ) return "";
    return value.Value;
}

typedef struct
{
    struct
    {
        f32 Column[4];
    } Row[3];
} TMatrix4x3;

typedef struct
{
    struct
    {
        f32 Column[4];
    } Row[4];
} TMatrix4x4;

#endif // #ifndef TYPES_H
