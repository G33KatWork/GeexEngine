-- simple.VS
uniform mat4 worldViewProjection;

attribute vec3 Position;
attribute vec3 Color;

varying vec3 fColor;

void main()
{
    gl_Position = worldViewProjection * vec4(Position, 1.0);
    fColor = Color;
}


-- simple.FS
varying vec3 fColor;

void main()
{
    gl_FragColor = vec4(fColor, 1.0);
}
