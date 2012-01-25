//
//  removeUnreferenced.h
//  Preview3D
//
//  Created by Daniele Panozzo on 17/11/11.

#ifndef IGL_REMOVEUNREFERENCED_H
#define IGL_REMOVEUNREFERENCED_H

#include <Eigen/Core>
namespace igl 
{
  // [ NV, NF ] = removeUnreferenced( V,F,epsilon )
  // Remove unreferenced vertices from V, updating F accordingly
  //
  // Input:
  // V,F: mesh description
  //
  // Output:
  // NV, NF: new mesh without unreferenced vertices
  
  template <typename T>
  inline void removeUnreferenced(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V, const Eigen::MatrixXi &F, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &NV, Eigen::MatrixXi &NF, Eigen::VectorXi &I);
  
}

// Implementation
template <typename T>
inline void igl::removeUnreferenced(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V, const Eigen::MatrixXi &F, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &NV, Eigen::MatrixXi &NF, Eigen::VectorXi &I)
{

  // Mark referenced vertices
  Eigen::MatrixXi mark = Eigen::MatrixXi::Zero(V.rows(),1);
  
  for(int i=0; i<F.rows(); ++i)
  {
    for(int j=0; j<F.cols(); ++j)
    {
      if (F(i,j) != -1)
        mark(F(i,j),0) = 1;
    }
  }
  
  // Sum the occupied cells 
  int newsize = mark.sum();
  
  NV = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>(newsize,V.cols());
  NF = Eigen::MatrixXi(F.rows(),F.cols());
  I  = Eigen::MatrixXi(V.rows(),1);
  
  // Do a pass on the marked vector and remove the unreferenced vertices
  int count = 0;
  for(int i=0;i<mark.rows();++i)
  {
    if (mark(i) == 1)
    {
      NV.row(count) = V.row(i);
      I(i) = count;
      count++;
    }
    else
    {
      I(i) = -1;
    }
  }
  
  // Apply I on F
      
  count = 0;
  for (int i =0; i<F.rows(); ++i)
  {
    int v0 = I[F(i,0)];
    int v1 = I[F(i,1)];
    int v2 = I[F(i,2)];
    if ( (v0 != v1) && (v2 != v1) && (v0 != v2) )
      NF.row(count++) << v0, v1, v2;
  }
}

#endif