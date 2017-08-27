// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'

#ifndef SPEEDTREE_COMMON_INCLUDED
#define SPEEDTREE_COMMON_INCLUDED

#include "UnityCG.cginc"

#define SPEEDTREE_Y_UP

#ifdef GEOM_TYPE_BRANCH_DETAIL
	#define GEOM_TYPE_BRANCH
#endif

// #include "SpeedTreeVertex_Master.cginc"
#define LOD_FADE_PERCENTAGE
#include "SpeedTreeVertex.cginc"
#undef LOD_FADE_PERCENTAGE

// Define Input structure

struct Input
{
	fixed4 color;
	half3 interpolator1;
	#ifdef GEOM_TYPE_BRANCH_DETAIL
		half3 interpolator2;
	#endif
	
	float4 screenPos;
	half transparency;
};
	
// Define uniforms

#define mainTexUV interpolator1.xy
sampler2D _MainTex;

UNITY_INSTANCING_CBUFFER_START(Fading)
	// UNITY_DEFINE_INSTANCED_PROP(half, master_LODFadeFull)
	UNITY_DEFINE_INSTANCED_PROP(half, master_LODFadeDetail)
UNITY_INSTANCING_CBUFFER_END

#ifdef GEOM_TYPE_BRANCH_DETAIL
	#define Detail interpolator2
	sampler2D _DetailTex;
#endif

#if defined(GEOM_TYPE_FROND) || defined(GEOM_TYPE_LEAF) || defined(GEOM_TYPE_FACING_LEAF)
	#define SPEEDTREE_ALPHATEST
	fixed _Cutoff;
#endif

#ifdef EFFECT_HUE_VARIATION
	#define HueVariationAmount interpolator1.z
	half4 _HueVariation;
#endif

#if defined(EFFECT_BUMP) && !defined(LIGHTMAP_ON)
	sampler2D _BumpMap;
#endif

fixed4 _Color;

#define LOD_TRANZITION_THRESHOLD 3.0
float _TreeSystemDistance;

// Vertex processing

void SpeedTreeVert(inout SpeedTreeVB IN, out Input OUT)
{
	UNITY_INITIALIZE_OUTPUT(Input, OUT);
	
	OUT.mainTexUV = IN.texcoord.xy;
	OUT.color = _Color;
	OUT.color.rgb *= IN.color.r; // ambient occlusion factor
	
	float3 campos = _WorldSpaceCameraPos;
	float3 pos = float3(unity_ObjectToWorld[0].w, unity_ObjectToWorld[1].w, unity_ObjectToWorld[2].w);

	float dist = distance(pos, campos);

	if (dist > _TreeSystemDistance - LOD_TRANZITION_THRESHOLD)
	{
		OUT.transparency = (_TreeSystemDistance - dist) / LOD_TRANZITION_THRESHOLD;
	}
	else
	{
		OUT.transparency = 1;
	}

	#ifdef EFFECT_HUE_VARIATION
		float hueVariationAmount = frac(unity_ObjectToWorld[0].w + unity_ObjectToWorld[1].w + unity_ObjectToWorld[2].w);
		hueVariationAmount += frac(IN.vertex.x + IN.normal.y + IN.normal.x) * 0.5 - 0.3;
		OUT.HueVariationAmount = saturate(hueVariationAmount * _HueVariation.a);
	#endif

	#ifdef GEOM_TYPE_BRANCH_DETAIL
		// The two types are always in different sub-range of the mesh so no interpolation (between detail and blend) problem.
		OUT.Detail.xy = IN.texcoord2.xy;
		if (IN.color.a == 0) // Blend
			OUT.Detail.z = IN.texcoord2.z;
		else // Detail texture
			OUT.Detail.z = 2.5f; // stay out of Blend's .z range
	#endif

	OffsetSpeedTreeVertex(IN, UNITY_ACCESS_INSTANCED_PROP(master_LODFadeDetail));
}

// Fragment processing

#if defined(EFFECT_BUMP) && !defined(LIGHTMAP_ON)
	#define SPEEDTREE_DATA_NORMAL			fixed3 Normal;
	#define SPEEDTREE_COPY_NORMAL(to, from)	to.Normal = from.Normal;
#else
	#define SPEEDTREE_DATA_NORMAL
	#define SPEEDTREE_COPY_NORMAL(to, from)
#endif

#define SPEEDTREE_COPY_FRAG(to, from)	\
	to.Albedo = from.Albedo;			\
	to.Alpha = from.Alpha;				\
	SPEEDTREE_COPY_NORMAL(to, from)

struct SpeedTreeFragOut
{
	fixed3 Albedo;
	fixed Alpha;
	SPEEDTREE_DATA_NORMAL
};

void SpeedTreeFrag(Input IN, out SpeedTreeFragOut OUT)
{
	half4 diffuseColor = tex2D(_MainTex, IN.mainTexUV);

	OUT.Alpha = diffuseColor.a * _Color.a;
	#ifdef SPEEDTREE_ALPHATEST
		clip(OUT.Alpha - _Cutoff);
	#endif

		
	{
		const float4x4 thresholdMatrix =
		{ 
			1.0 / 17.0,  9.0 / 17.0,  3.0 / 17.0, 11.0 / 17.0,
			13.0 / 17.0,  5.0 / 17.0, 15.0 / 17.0,  7.0 / 17.0,
			4.0 / 17.0, 12.0 / 17.0,  2.0 / 17.0, 10.0 / 17.0,
			16.0 / 17.0,  8.0 / 17.0, 14.0 / 17.0,  6.0 / 17.0
		};
		const float4x4 _RowAccess = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
		float2 pos = IN.screenPos.xy / IN.screenPos.z;
		pos *= _ScreenParams.xy;

		// clip(UNITY_ACCESS_INSTANCED_PROP(master_LODFadeFull) - thresholdMatrix[fmod(pos.x, 4)] * _RowAccess[fmod(pos.y, 4)]);
		clip(IN.transparency - thresholdMatrix[fmod(pos.x, 4)] * _RowAccess[fmod(pos.y, 4)]);
	}
	

	#ifdef GEOM_TYPE_BRANCH_DETAIL
		half4 detailColor = tex2D(_DetailTex, IN.Detail.xy);
		diffuseColor.rgb = lerp(diffuseColor.rgb, detailColor.rgb, IN.Detail.z < 2.0f ? saturate(IN.Detail.z) : detailColor.a);
	#endif

	#ifdef EFFECT_HUE_VARIATION
		half3 shiftedColor = lerp(diffuseColor.rgb, _HueVariation.rgb, IN.HueVariationAmount);
		half maxBase = max(diffuseColor.r, max(diffuseColor.g, diffuseColor.b));
		half newMaxBase = max(shiftedColor.r, max(shiftedColor.g, shiftedColor.b));
		maxBase /= newMaxBase;
		maxBase = maxBase * 0.5f + 0.5f;
		// preserve vibrance
		shiftedColor.rgb *= maxBase;
		diffuseColor.rgb = saturate(shiftedColor);
	#endif

	OUT.Albedo = diffuseColor.rgb * IN.color.rgb;

	#if defined(EFFECT_BUMP) && !defined(LIGHTMAP_ON)
		OUT.Normal = UnpackNormal(tex2D(_BumpMap, IN.mainTexUV));
	#endif
}

#endif // SPEEDTREE_COMMON_INCLUDED
