#include "../include/RutherfordHit.hh"

#include <G4ParticleTable.hh>
#include <G4ProcessManager.hh>
#include <G4VProcess.hh>

#include <G4Types.hh>
#include <vector>

RutherfordHit::RutherfordHit(G4Step* step)
{
	auto* track         = step->GetTrack();
	auto* preStepPoint  = step->GetPreStepPoint();
	auto* postStepPoint = step->GetPostStepPoint();
	auto* process       = postStepPoint->GetProcessDefinedStep();

	fTrackID            = track->GetTrackID();
	fParentTrackID      = track->GetParentID();
	fPDGCode            = track->GetParticleDefinition()->GetPDGEncoding();
	fProcessType        = process->GetProcessType();
	fProcessSubType     = process->GetProcessSubType();
	fEnergyDeposit      = step->GetTotalEnergyDeposit();
	fPosition           = preStepPoint->GetPosition();
	fTime               = preStepPoint->GetGlobalTime();
}

G4VProcess* RutherfordHit::GetProcess() const
{
	auto* particleTable = G4ParticleTable::GetParticleTable();

	auto* particleDefinition = particleTable->FindParticle(fPDGCode);
	if  (!particleDefinition) return nullptr;
	
	auto* processManager = particleDefinition->GetProcessManager();
	if  (!processManager) return nullptr;

	auto* processList = processManager->GetProcessList();
	for (G4int i = 0; i < processList->entries(); ++i)
	{
		auto* process = (*processList)[i];
		if  (!process) continue;

		if (
			process->GetProcessType()    == fProcessType &&
			process->GetProcessSubType() == fProcessSubType
		)
			return process;
	}

	return nullptr;
}