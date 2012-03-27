template <>
void NavierStokesSolver<host_memory>::generateBC2()
{
	int  nx = domInfo->nx,
	     ny = domInfo->ny;
	//int  numP  = nx*ny;
	
	real *dx = thrust::raw_pointer_cast(&(domInfo->dx[0])),
	     *dy = thrust::raw_pointer_cast(&(domInfo->dy[0]));
	
	/// rhs2 of size np+2nb
	
	/// boundary conditions from the continuity equations
		
	cusp::blas::fill(bc2, 0.0);
	
	for(int i=0; i<nx; i++)
	{
		bc2[i] -= bc[YMINUS][i+nx-1]*dx[i]; // v[0][i+1]*dx;
		bc2[(ny-1)*nx + i] += bc[YPLUS][i+nx-1]*dx[i]; // v[ny][i+1]*dx;
	}

	for(int j=0; j<ny; j++)
	{
		// left
		bc2[j*nx] -= bc[XMINUS][j]*dy[j]; // u[j+1][0]*dy;
		// right
		bc2[j*nx+nx-1] += bc[XPLUS][j]*dy[j]; // u[j+1][nx]*dy;
	}
}

template <>
void NavierStokesSolver<device_memory>::generateBC2()
{
	int  nx = domInfo->nx,
	     ny = domInfo->ny;
	
	real *dx = thrust::raw_pointer_cast(&(domInfo->dx[0])),
	     *dy = thrust::raw_pointer_cast(&(domInfo->dy[0]));
	
	/// rhs2 of size np
	cusp::blas::fill(bc2Host, 0.0);
	
	/// boundary conditions from the continuity equations
	for(int i=0; i<nx; i++)
	{
		bc2Host[i] -= bcHost[YMINUS][i+nx-1]*dx[i]; // v[0][i+1]*dx;
		bc2Host[(ny-1)*nx + i] += bcHost[YPLUS][i+nx-1]*dx[i]; // v[ny][i+1]*dx;
	}

	for(int j=0; j<ny; j++)
	{
		// left
		bc2Host[j*nx] -= bcHost[XMINUS][j]*dy[j]; // u[j+1][0]*dy;
		// right
		bc2Host[j*nx+nx-1] += bcHost[XPLUS][j]*dy[j]; // u[j+1][nx]*dy;
	}
	bc2 = bc2Host;
}
/*
template<>
void NavierStokesSolver<cooD, vecD>::generateBC2()
{
	// raw pointers for cup arrays
	real *H_r  = thrust::raw_pointer_cast(&H[0]),
	     *q_r  = thrust::raw_pointer_cast(&q[0]),
	     *rn_r = thrust::raw_pointer_cast(&rn[0]),
	     *dxD = thrust::raw_pointer_cast(&(domInfo->dxD[0])),
	     *dyD = thrust::raw_pointer_cast(&(domInfo->dyD[0]));
	
	real *xminus = thrust::raw_pointer_cast(&(bc[XMINUS][0])),
	     *xplus  = thrust::raw_pointer_cast(&(bc[XPLUS][0])),
	     *yminus = thrust::raw_pointer_cast(&(bc[YMINUS][0])),
	     *yplus  = thrust::raw_pointer_cast(&(bc[YPLUS][0]));
	
	int  nx = domInfo->nx,
	     ny = domInfo->ny;
	
	
}
*/