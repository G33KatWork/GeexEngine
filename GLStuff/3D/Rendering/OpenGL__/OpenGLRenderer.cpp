#include <3D/Rendering/OpenGL/OpenGLRenderer.h>

OpenGLRenderer::OpenGLRenderer(int width, int height)
    : Renderer(width, height)
{}

void OpenGLRenderer::Resize(int newWidth, int newHeight)
{
	Renderer::Resize(newWidth, newHeight);
	glViewport(0, 0, newWidth, newHeight);

	//FIXME: Recalculate world view projection stuff
}

bool OpenGLRenderer::BeginScene()
{
    glBegin(GL_TRIANGLE_STRIP);
	return true;
}

void OpenGLRenderer::EndScene()
{
    glEnd();
}

void OpenGLRenderer::ClearBackBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::ClearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::ClearStencilBuffer()
{
    glClear(GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderer::ClearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderer::SetWorldMatrix(Matrix4 m)
{
	
}

void OpenGLRenderer::SetViewMatrix(Matrix4 m)
{
	
}

void OpenGLRenderer::SetProjectionMatrix(Matrix4 m)
{
	
}

void OpenGLRenderer::SetBackgroundColor(Color newColor)
{
	Renderer::SetBackgroundColor(newColor);
	glClearColor(newColor.R(), newColor.G(), newColor.B(), newColor.A());
}

void OpenGLRenderer::UpdateCamera(ICamera* camera)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(ToOGLMatrix(camera->GetProjectionMatrix()).m);
	glMultMatrixf(ToOGLMatrix(camera->GetViewMatrix()).m);
	glMatrixMode(GL_MODELVIEW);
}

OGLMATRIX OpenGLRenderer::ToOGLMatrix(Matrix4 m)
{
	OGLMATRIX d;

	d.m[0] = m[0][0];
	d.m[1] = m[1][0];
	d.m[2] = m[2][0];
	d.m[3] = m[3][0];

	d.m[4] = m[0][1];
	d.m[5] = m[1][1];
	d.m[6] = m[2][1];
	d.m[7] = m[3][1];

	d.m[8] = m[0][2];
	d.m[9] = m[1][2];
	d.m[10] = m[2][2];
	d.m[11] = m[3][2];
    
	d.m[12] = m[0][3];
	d.m[13] = m[1][3];
	d.m[14] = m[2][3];
	d.m[15] = m[3][3];

	return d;
}