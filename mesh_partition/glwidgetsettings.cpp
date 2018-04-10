#include "glwidgetsettings.h"


//////////////////////////////////////////////////////////////////////////
// Class GLWidgetSettings
GLWidgetSettings::GLWidgetSettings()
{
	init();
}

GLWidgetSettings::~GLWidgetSettings()
{
	clear();
}

void GLWidgetSettings::init()
{
	point_size_ = 5.0;
	line_size_ = light_brightness_ = 1.5;
	enable_boundingbox_ = false;
	enable_lighting_ = false;

	point_ambient[0] = 0.2f; point_ambient[1] = 0.2f; point_ambient[2] = 0.2f; point_ambient[3] = 1.0f;
	point_diffuse[0] = 0.8f; point_diffuse[1] = 0.8f; point_diffuse[2] = 0.8f; point_diffuse[3] = 1.0f;

	line_ambient[0] = 0.2f; line_ambient[1] = 0.2f; line_ambient[2] = 0.2f; line_ambient[3] = 1.0f;
	line_diffuse[0] = 0.0f; line_diffuse[1] = 0.0f; line_diffuse[2] = 0.0f; line_diffuse[3] = 1.0f;

	feature_ambient[0] = 1.0f; feature_ambient[1] = 0.0f; feature_ambient[2] = 0.0f; feature_ambient[3] = 1.0;
	feature_diffuse[0] = 1.0f; feature_diffuse[1] = 0.0f; feature_diffuse[2] = 0.0f; feature_diffuse[3] = 1.0;
	face_shinnes = 30;
	feature_line_size = 10;

	border_ambient[0] = 1.0f; border_ambient[1] = 1.0f; border_ambient[2] = 0.0f; border_ambient[3] = 1.0f;
	border_diffuse[0] = 1.0f; border_diffuse[1] = 1.0f; border_diffuse[2] = 0.0f; border_diffuse[3] = 1.0f;

	other_ambient[0] = 0.5f; other_ambient[1] = 0.2f; other_ambient[2] = 0.5f; other_ambient[3] = 1.0f;
	other_diffuse[0] = 0.4f; other_diffuse[1] = 0.5f; other_diffuse[2] = 0.6f; other_diffuse[3] = 1.0f;

	visibility_ambient[0] = 0.0f; visibility_ambient[1] = 1.0f; visibility_ambient[2] = 1.0f; visibility_ambient[3] = 1.0f;
	visibility_diffuse[0] = 0.0f; visibility_diffuse[1] = 1.0f; visibility_diffuse[2] = 1.0f; visibility_diffuse[3] = 1.0f;

	face_ambient[0] = 0.2f; face_ambient[1] = 0.2f; face_ambient[2] = 0.2f; face_ambient[3] = 1.0f;
	face_diffuse[0] = 0.5f; face_diffuse[1] = 1.0f; face_diffuse[2] = 0.0f; face_diffuse[3] = 1.0f;
	point_shinness = 20; line_shinness = 20; face_shinnes = 15; border_shinnes = 20; other_shinnes = 5; visibility_shinnes = 4;

	reset();
}

void GLWidgetSettings::clear()
{
	init();
}

void GLWidgetSettings::reset()
{
	xshift_ = 0.0;
	yshift_ = 0.0;
	zshift_ = 0.0;
	clipping = 0.0;

	// create identity matrix
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			transformation_[i][j] = (i == j) ? 1.0f : 0.0f;
}