#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"

#include "EventAction.hh"
#include "Configure.hh"

EventAction::EventAction()
    : G4UserEventAction(), event_num(0)
{
	
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *)
{
}

void EventAction::EndOfEventAction(const G4Event *anEvent)
{
    auto HCE = anEvent->GetHCofThisEvent();
    if (!HCE)
        return;
    
    char ID[Maximum_E/E_bin*particle_num];
    int j = 0;
    int n;
    
    for(G4int k = 0; k < particle_num; k++){
    	n = 0;
    	for(G4int i = 0; i < Maximum_E; i = i+E_bin){
    		// print spectrum
    		G4String results = "Detector/";
    		results += particle[k];
    		std::sprintf(ID, " %dMeV",i);
    		G4String id(ID);
    		results += id;
    		if(event_num == 0)
    			fHCID[j] = G4SDManager::GetSDMpointer()->GetCollectionID(results);
    		auto hitsMap = static_cast<G4THitsMap<G4double> *>(HCE->GetHC(fHCID[j]));
    		for(const auto &iter : *(hitsMap->GetMap())){
    			auto count = *(iter.second);
    			//G4cout << "*--- Number of " << results << ": " << count << "---* << G4endl;
    			spectrum[k][n] += count;
    		}
    		j++;
    		n++;
    	}
    }
    event_num++;
    
    if(event_num == event_end_num){
    	for(G4int k = 0; k < particle_num; k++){
    		auto spectrum_k = particle[k];
    		spectrum_k += ": ";
    		n = 0;
    		for(G4int i = 0; i < Maximum_E; i = i+E_bin){
    			spectrum_k += std::__cxx11::to_string(spectrum[k][n]);
    			spectrum_k += ", ";
    			n++;
    		}
    		G4cout << spectrum_k << G4endl;
    	}
    }
}
