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
	with alive_bar(n_hits, title="Analyzing hits") as bar:
		for hit in tree:

			eventID  = hit.EventID
			Edep     = hit.Edep_keV
			parentID = hit.ParentTrackID
			time     = hit.T_ns + eventID * 1e6  # ns (to separate events in time graph)

			if   parentID == 0:
				event_to_Edep_prime[eventID] = event_to_Edep_prime.get(eventID, 0) + Edep
				n_hits_prime += 1
			elif parentID == 1:
				event_to_Edep_second[eventID] = event_to_Edep_second.get(eventID, 0) + Edep
				n_hits_second += 1

			bar()

	file.Close()

	file = ROOT.TFile(args.output_file, "RECREATE")
	
	n_events = len(event_to_Edep_prime)
 
	histoEdepPrime = ROOT.TH1F("histoEdepPrime", "Total Energy Deposit per Event;Edep [keV];Counts", 1000, 0, 10)
	for Edep in event_to_Edep_prime.values():
		histoEdepPrime.Fill(Edep)
	histoEdepPrime.Write()
 
	histoEdepSecond = ROOT.TH1F("histoEdepSecond", "Total Energy Deposit per Event;Edep [keV];Counts", 1000, 0, 10)
	for Edep in event_to_Edep_second.values():
		histoEdepSecond.Fill(Edep)
	histoEdepSecond.Write()

	file.Close()

	print(f"hits   per event = {n_hits       /n_events:.2f}")
	print(f"hits'  per event = {n_hits_prime /n_events:.2f}")
	print(f"hits'' per event = {n_hits_second/n_events:.2f}")

if __name__ == "__main__":
	main()