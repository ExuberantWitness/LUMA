/*
* --------------------------------------------------------------
*
* ------ Lattice Boltzmann @ The University of Manchester ------
*
* -------------------------- L-U-M-A ---------------------------
*
*  Copyright (C) 2015, 2016
*  E-mail contact: info@luma.manchester.ac.uk
*
* This software is for academic use only and not available for
* distribution without written consent.
*
*/

#pragma once

#include "GridObj.h"

/// \brief	GridUnits.
///
///			This class contains static methods for unit conversion.
///         Partial implementation only.
class GridUnits
{
public:
	GridUnits(){};
	~GridUnits(){};

	///< Convert from m to cm
	template <typename T>
	static T m2cm(const T meters) { return meters * 100; }

	// *****************************************************************************
	/// \brief	Velocity in lattice units to velocity in physical units.
	///
	///			Converts velocity component from lattice units to m/s. 
	///         It uses the L_PHYSICAL_U introduced by the user, dh and dt. 
	///			You can introduce any L_PHYSICAL_U you want, but the reference length 
	///			(usually the width of the domain), the Re number and the LBM parameters 
	///			will remain the same. So you will be implicitly changing the physical viscosity
	///         of your fluid when you change L_PHYSICAL_U.
	///
	/// \param u_lattice	Lattice velocity.
	/// \param currentGrid	Pointer to the current grid. 
	/// \return physical velocity
	template <typename T>
	static double ulat2uphys(T u_lattice, GridObj* currentGrid)
	{
		return (u_lattice * currentGrid->dh * L_PHYSICAL_U) / currentGrid->dt;
	}
	
	// *****************************************************************************
	/// \brief	Converts velocity in dimensionless units to LBM units.
	///
	/// \param u_dimensionless	Dimensionless velocity.
	/// \param currentGrid		Pointer to the current grid. 
	/// \return velocity in LBM units.
	template <typename T>
	static double ud2ulbm(T u_dimensionless, GridObj* currentGrid)
	{
		return (u_dimensionless * currentGrid->dt) / currentGrid->dh;
	}

	// *****************************************************************************
	/// \brief	Converts length in dimensionless units to LBM units.
	///
	/// \param l_dimensionless	Dimensionless length.
	/// \param currentGrid Pointer to the current grid. 
	/// \return LBM length
	template <typename T>
	static double ld2llbm(T l_dimensionless, GridObj* currentGrid)
	{
		return l_dimensionless / currentGrid->dh;
	}

	// *****************************************************************************
	/// \brief	Converts kinematic viscosity in dimensionless units to LBM units.
	///
	/// \param nu_dimensionless		Dimensionless kinematic viscosity.
	/// \param currentGrid			Pointer to the current grid. 
	/// \return kinematic viscosity in LBM units.
	template <typename T>
	static double nud2nulbm(T nu_dimensionless, GridObj* currentGrid)
	{
		return (nu_dimensionless * currentGrid->dt) / (SQ(currentGrid->dh));
	}

	// *****************************************************************************
	/// \brief	Converts acceleration in dimensionless units to LBM units.
	///
	/// \param a_dimensionless	Dimensionless acceleration.
	/// \param currentGrid		Pointer to the current grid. 
	/// \return acceleration in LBM units.
	template <typename T>
	static double fd2flbm(T a_dimensionless, GridObj* currentGrid)
	{
		return (a_dimensionless * SQ(currentGrid->dt)) / currentGrid->dh;
	}

	// *****************************************************************************
	/// \brief	Converts seconds into hours, minutes and seconds.
	///
	/// \param total_seconds	number of seconds to be converted.
	/// \param[out] hms			pointer to an integer array of size 3 contianing 
	///							hours minutes and seconds.
	template <typename T>
	static void secs2hms(T total_seconds, int *hms)
	{
		// Round to the nearest second
		total_seconds = std::round(total_seconds);

		// Compute number of hours and minutes represented
		double hours = static_cast<double>(total_seconds) / (60.0 * 60.0);
		double minutes = static_cast<double>(total_seconds) / 60.0;

		// Compute components
		hms[0] = static_cast<int>(std::floor(hours));
		hms[1] = static_cast<int>(std::floor(minutes - (static_cast<double>(hms[0]) * 60.0)));
		hms[2] = static_cast<int>(std::floor(
			static_cast<double>(total_seconds) - 
			static_cast<double>(hms[1]) * 60.0 - 
			static_cast<double>(hms[0]) * 60.0 * 60.0
			));
	}

	// *****************************************************************************
	/// \brief	Converts pressure in dimensionless units to density in LBM units.
	///
	/// \param p_dimensionless	Dimensionless pressure.
	/// \param currentGrid		Pointer to the current grid. 
	/// \return density in LBM units.
	template <typename T>
	static double pd2dlbm(T p_dimensionless, GridObj* currentGrid)
	{
		return (p_dimensionless * currentGrid->dh * SQ(currentGrid->dt) / currentGrid->dm) / SQ(cs);
	}
	
};

