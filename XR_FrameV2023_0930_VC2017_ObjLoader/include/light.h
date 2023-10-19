#pragma once
//-------- light.cpp

void MainLight( int light_id, float r, float g, float b );
void SubLight( int light_id, float r, float g, float b);
void HeadLight( int light_id, float r, float g, float b, float att );
void Fog( int fog_mode, float r, float g, float b, float d, float start, float end );
void SpotLight( int light_id, float r, float g, float b, float att_half, 
	float cutoff, int exponent );
void PointLight( int light_id, float r, float g, float b, float att_half );

void HeadLight( void );
void Lighting( void );
void setFog( void );
