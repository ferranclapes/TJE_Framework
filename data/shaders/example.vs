attribute vec2 a_uv;
attribute vec3 a_vertex;

varying vec2 v_uv;

void main()
{
    v_uv = a_uv;

    // Don’t apply transformations to the vertex!
    gl_Position = vec4(a_vertex, 1.0);
}
