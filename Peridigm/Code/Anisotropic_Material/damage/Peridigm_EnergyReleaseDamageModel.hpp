/*! \file Peridigm_EnergyReleaseDamageModel.hpp */

//@HEADER
// ************************************************************************
//
//                             Peridigm
//                 Copyright (2011) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions?
// David J. Littlewood   djlittl@sandia.gov
// John A. Mitchell      jamitch@sandia.gov
// Michael L. Parks      mlparks@sandia.gov
// Stewart A. Silling    sasilli@sandia.gov
//
// ************************************************************************
//////////////////////////////////////////////////////////////////////////////////////    
// Routine developed for Peridigm by
// DLR Composite Structures and Adaptive Systems
//                                __/|__
//                                /_/_/_/  
//            www.dlr.de/fa/en      |/ DLR
//////////////////////////////////////////////////////////////////////////////////////    
// Questions?
// Christian Willberg  christian.willberg@dlr.de
// Martin Raedel       martin.raedel@dlr.de
// https://github.com/PeriDoX/
//////////////////////////////////////////////////////////////////////////////////////    
//@HEADER


#ifndef PERIDIGM_ENERGYRELEASEDAMAGEMODEL_HPP
#define PERIDIGM_ENERGYRELEASEDAMAGEMODEL_HPP

#include "Peridigm_DamageModel.hpp"
#include "Peridigm_Material.hpp"
#include "Peridigm_InfluenceFunction.hpp"
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Epetra_Vector.h>
#include <Epetra_Map.h>

namespace PeridigmNS {

  //! Base class defining the Peridigm damage model interface.
  class EnergyReleaseDamageModel : public DamageModel{

  public:
	
    //! Standard constructor.
    EnergyReleaseDamageModel(const Teuchos::ParameterList& params);

    //! Destructor.
    virtual ~EnergyReleaseDamageModel();

    //! Return name of the model.
    virtual std::string Name() const { return("Energy Release"); }

    //! Returns a vector of field IDs corresponding to the variables associated with the model.
    virtual std::vector<int> FieldIds() const { return m_fieldIds; }
     
    //! Returns the bulk modulus of the material.
    virtual double BulkModulus() const { return m_bulkModulus; }

    //! Returns the shear modulus of the material.
    virtual double ShearModulus() const { return m_shearModulus; }
    //! Initialize the damage model.
    virtual void
    initialize(const double dt,
                  const int numOwnedPoints,
                  const int* ownedIDs,
                  const int* neighborhoodList,
                  PeridigmNS::DataManager& dataManager) const ;
    
    virtual void
    computeDamage(const double dt,
                  const int numOwnedPoints,
                  const int* ownedIDs,
                  const int* neighborhoodList,
                  PeridigmNS::DataManager& dataManager) const ;
    int checkDetachedNodes(
                       const int numOwnedPoints,
                       const int* ownedIDs,
                       const int* neighborhoodList,
                       PeridigmNS::DataManager& dataManager) const ;
    //virtual void
    //computeDilatation(const int numOwnedPoints,
    //              const int* ownedIDs,
    //              const int* neighborhoodList,
    //              const double BM,
    //              const double SM,
    //              PeridigmNS::DataManager& dataManager) const ;              
                  

        PeridigmNS::InfluenceFunction::functionPointer m_OMEGA;
        
    protected:
        //! Computes the distance between nodes (a1, a2, a3) and (b1, b2, b3).
        inline double distance(double a1, double a2, double a3,
                               double b1, double b2, double b3) const
        {
          return ( sqrt( (a1-b1)*(a1-b1) + (a2-b2)*(a2-b2) + (a3-b3)*(a3-b3) ) );
        }
        
    double m_pi; 
    double m_criticalEnergyTension;
    double m_criticalEnergyCompression;
    double m_criticalEnergyShear;
    double m_bulkModulus;
    double m_shearModulus; 
    double m_alpha;
    bool m_applyThermalStrains;
    bool m_planeStrain;
    bool m_planeStress;
    bool m_onlyTension;
    bool detachedNodesCheck;
    int m_detachedNodesFieldId;
    // field ids for all relevant data
    std::vector<int> m_fieldIds;
    int m_modelCoordinatesFieldId;
    int m_coordinatesFieldId;
    int m_damageFieldId;    
    int m_bondDamageFieldId;
    int m_deltaTemperatureFieldId;
    int m_volumeFieldId;
    int m_dilatationFieldId;
    int m_weightedVolumeFieldId;
    double m_horizon;
    int m_horizonFieldId;
    int m_damageModelFieldId;
    int m_type;
    double m_Thickness;
	bool m_rot;
	double maxRad;
  };

}

#endif // PERIDIGM_ENERGYRELEASEDAMAGEMODEL_HPP
