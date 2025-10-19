import argparse

import ROOT

from alive_progress import alive_bar

def main():

	parser = argparse.ArgumentParser()
	parser.add_argument("input_dir",   type=str, default="./.data",               help="directory of simulation output and analysis input")
	parser.add_argument("output_file", type=str, default="./.data/analysis.root", help="path to analysis output file")
	args = parser.parse_args()
 
	ROOT.gROOT.SetBatch(True)
	ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
	ROOT.gErrorIgnoreLevel = ROOT.kFatal

	file = ROOT.TFile(args.input_dir, "READ")
	tree = file.Get("Hits")
	n_hits = tree.GetEntries()
	n_hits_prime  = 0
	n_hits_second = 0

	event_to_Edep_prime  = { }
	event_to_Edep_second = { }
	event_to_Edep_total  = { }
	with alive_bar(n_hits, title="Analyzing hits") as bar:
		for hit in tree:

			eventID  = hit.EventID
			Edep     = hit.Edep_keV
			parentID = hit.ParentTrackID
			time     = hit.T_ns

			if parentID == 0:
				event_to_Edep_prime[eventID] = event_to_Edep_prime.get(eventID, 0) + Edep
				n_hits_prime += 1
			else:
				event_to_Edep_second[eventID] = event_to_Edep_second.get(eventID, 0) + Edep
				n_hits_second += 1
			
			event_to_Edep_total[eventID] = event_to_Edep_total.get(eventID, 0) + Edep

			bar()

	file.Close()

	file = ROOT.TFile(args.output_file, "RECREATE")
	
	n_events = len(event_to_Edep_second)
 
	histoEdepPrime = ROOT.TH1F("histoEdepPrime", "Total Energy Deposit per Event;Edep [keV];Counts", 1000, 0, 6000)
	for Edep in event_to_Edep_prime.values():
		histoEdepPrime.Fill(Edep)
	histoEdepPrime.Write()
 
	histoEdepSecond = ROOT.TH1F("histoEdepSecond", "Total Energy Deposit per Event;Edep [keV];Counts", 1000, 0, 6000)
	for Edep in event_to_Edep_second.values():
		histoEdepSecond.Fill(Edep)
	histoEdepSecond.Write()
 
	histoEdepTotal = ROOT.TH1F("histoEdepTotal", "Total Energy Deposit per Event;Edep [keV];Counts", 1000, 0, 6000)
	for Edep in event_to_Edep_total.values():
		histoEdepTotal.Fill(Edep)
	histoEdepTotal.Write()

	file.Close()

	print(f"hits   per event = {n_hits       /n_events:.2f}")
	print(f"hits'  per event = {n_hits_prime /n_events:.2f}")
	print(f"hits'' per event = {n_hits_second/n_events:.2f}")

if __name__ == "__main__":
	main()
