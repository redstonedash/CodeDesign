#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPosition;
// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 modelPos = vec3(0,0,0);
uniform vec3 lightPos[@n] = float[@n](@i);
uniform vec3 cameraPos;
uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;
// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(62.01019,12.9898)))*
        43424.5453123);
}

float organicNoise (vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}


float hash(vec2 p)  // replace this by something better
{
    p  = 50.0*fract( p*0.3183099 + vec2(0.71,0.113));
    return -1.0+2.0*fract( p.x*p.y*(p.x+p.y) );
}

float nicerNoise( in vec2 p )
{
    vec2 i = floor( p );
    vec2 f = fract( p );
	
	vec2 u = f*f*(3.0-2.0*f);

    return mix( mix( hash( i + vec2(0.0,0.0) ), 
                     hash( i + vec2(1.0,0.0) ), u.x),
                mix( hash( i + vec2(0.0,1.0) ), 
                     hash( i + vec2(1.0,1.0) ), u.x), u.y);
}

// TODO: improve readability

float noiser( vec2 coord )
{
    vec2 p = coord.xy / 25;

	vec2 uv = p*vec2(1,1.0);
	
	float f = 0.0;
	uv *= 8.0;
    mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );
	f  = 0.5000*nicerNoise( uv ); uv = m*uv;
	f += 0.2500*nicerNoise( uv ); uv = m*uv;
	f += 0.1250*nicerNoise( uv ); uv = m*uv;
	f += 0.0625*nicerNoise( uv ); uv = m*uv;

	f = 0.5 + 0.5*f;	
	
	return f;
}

void main()
{
    // Texel color fetching from texture sampler
    vec3 position = (fragPosition) + modelPos;
    float modX = mod(position.x,10);
    if(modX >= 9.5f){
    	modX = sin(((modX-9.5f)/0.5f) * 3.14159265359);
    } else {
    	modX = 0;
    }
    float modZ = mod(position.z,10);
    if(modZ >= 9.5f){
    	modZ = sin(((modZ-9.5f)/0.5f) * 3.14159265359);
    } else {
    	modZ = 0;
    }
    vec3 normalNoise;
    normalNoise = vec3(sin(noiser(position.xz/4)*3.1415)/6,cos(noiser(position.xz/4)*3.1415)/6,cos(noiser(position.xz/4)*3.1415)/6);
    vec3 reflectedNormal = normalize(reflect(position - cameraPos, normalize(fragNormal + normalNoise - vec3(modX,modZ,0) + (normalNoise/3))));
    float noise = noiser(position.xz/5);
    /*//xy
    vec2 xy =
    vec2(organicNoise(position.xz-vec2(0.1f,0)/5),0.1f) -
    vec2(organicNoise(position.xz+vec2(0.1f,0)/5),-0.1f);
    xy = vec2(-xy.y, xy.x);
    //zy
	vec2 zy =
    vec2(organicNoise(position.xz-vec2(0,0.1f)/5),0.1f) -
    vec2(organicNoise(position.xz+vec2(0,0.1f)/5),-0.1f);
    xy = vec2(-zy.y, zy.x);
    normalNoise = normalize(vec3(xy.x,xy.y+zy.y,zy.x));*/
    


    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
    float lighDistance = distance(lightPos,position);
    position.y += noise * 2.5;
    vec3 surfaceDir = reflectedNormal;
    float lightDirectness = dot(normalize(lightPos - position),surfaceDir);
    float lightFinalBrightness = lightDirectness/(distance(lightPos,position)/2);
    float reflectiveColor = pow(1/(distance(lightPos, position+(normalize(surfaceDir)*(lighDistance)))*0.5),2);
    //finalColor = vec4(position,1);
    //finalColor = vec4(reflectiveColor,reflectiveColor,reflectiveColor,1);//lightFinalBrightness,lightFinalBrightness,lightFinalBrightness,1);
    float finalBrightness = ((lightFinalBrightness*(cos(noiser(position.xz/3)*3.1415)))+(reflectiveColor*(1-cos(noiser(position.xz/3)*3.1415))));
   	finalColor = vec4(finalBrightness*0.98,finalBrightness*1.2,finalBrightness*1.4,1+(fragPosition.y/5));
}