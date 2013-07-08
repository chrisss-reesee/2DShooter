#include "Vector2D.h"
#include "C2DMatrix.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << " " << rhs.x << " " << rhs.y;

  return os;
}

  
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
  is >> lhs.x >> lhs.y;

  return is;
}


//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors from the objects local space into world space
//------------------------------------------------------------------------
std::vector<Vector2D> TransformFromLocalToWorldSpace(std::vector<Vector2D> &points,
                                            const Vector2D   &pos,
                                            const Vector2D   &forward,
                                            const Vector2D   &side,
                                            const Vector2D   &scale)
{
	//copy the original vertices into the buffer about to be transformed
  std::vector<Vector2D> TranVector2Ds = points;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
  if ( (scale.x != 1.0) || (scale.y != 1.0) )
  {
	  matTransform.Scale(scale.x, scale.y);
  }

	//rotate
	matTransform.Rotate(side, forward);	// changed

	//and translate
	matTransform.Translate(pos.x, pos.y);
	
  //now transform the object's vertices
  matTransform.TransformVector2Ds(TranVector2Ds);

  return TranVector2Ds;
}

//--------------------------- WorldTransform -----------------------------
//
//  given a std::vector of 2D vectors, a position, orientation and scale,
//  this function transforms the 2D vectors from the objects local space into world space
//------------------------------------------------------------------------
Vector2D TransformFromLocalToWorldSpace( Vector2D &point,
                                            const Vector2D   &pos,
                                            const Vector2D   &forward,
                                            const Vector2D   &side,
                                            const Vector2D   &scale)
{
	//copy the original vertices into the buffer about to be transformed
  Vector2D transpoint = point;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
  if ( (scale.x != 1.0) || (scale.y != 1.0) )
  {
	  matTransform.Scale(scale.x, scale.y);
  }

	//rotate
	matTransform.Rotate(side, forward);	// changed

	//and translate
	matTransform.Translate(pos.x, pos.y);
	
  //now transform the object's vertices
  matTransform.TransformVector2Ds(transpoint);

  return transpoint;
}

//--------------------- PointToLocalSpace --------------------------------
//
//------------------------------------------------------------------------
Vector2D TransformFromWorldToLocalSpace(const Vector2D &point,
                             Vector2D &AgentSide,
                             Vector2D &AgentHeading,
                              Vector2D &AgentPosition)
{

	//make a copy of the point
  Vector2D TransPoint = point;
  
  //create a transformation matrix
	C2DMatrix matTransform;

  double Tx = -AgentPosition.Dot(AgentHeading);
  double Ty = -AgentPosition.Dot(AgentSide);

  //create the transformation matrix
  matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
  matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
  matTransform._31(Tx);           matTransform._32(Ty);
	
  //now transform the vertices
  matTransform.TransformVector2Ds(TransPoint);
	TransPoint.x = -TransPoint.x;
  return TransPoint;
}


