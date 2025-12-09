import argparse
import numpy
import ROOT

def main():

	# Argument Pareser
	parser = argparse.ArgumentParser()
	parser.add_argument("input_file",           type=str,   default="./.data",               help="directory of simulation output and analysis input")
	parser.add_argument("output_file",          type=str,   default="./.data/analysis.root", help="path to analysis output file")
	parser.add_argument("-j", "--jobs",         type=int,   default=1,                       help="number of jobs")
	parser.add_argument("-p", "--prime-parent", type=int,   default=0,                       help="parent ID of primary track")
	parser.add_argument("-b", "--e-bins",       type=int,   default=1000,                    help="number of bins for spectrum histogram")
	parser.add_argument("-i", "--e-min",        type=float, default=0,                       help="minimum energy in keV")
	parser.add_argument("-u", "--e-max",        type=float, default=6000,                    help="maximum energy in keV")
	args = parser.parse_args()

	# ROOT Init
	ROOT.gROOT.SetBatch(True)
	ROOT.gEnv.SetValue("WebGui.StartHttp", "no")
	ROOT.gErrorIgnoreLevel = ROOT.kFatal
	ROOT.ROOT.EnableImplicitMT(args.jobs)

	dataframe = ROOT.RDataFrame("Hits", args.input_file)
	hits_data = dataframe.AsNumpy(["EventID", "Edep_keV", "ParentTrackID", "T_ns"])

	eventID   = hits_data["EventID"]
	Edep      = hits_data["Edep_keV"]
	parentID  = hits_data["ParentTrackID"]

	_, inverse = numpy.unique(eventID, return_inverse=True)

	mask_prime  = parentID == args.prime_parent
	mask_second = parentID >  args.prime_parent

	event_Edep_total  = numpy.bincount(inverse, weights=Edep              )
	event_Edep_prime  = numpy.bincount(inverse, weights=Edep * mask_prime )
	event_Edep_second = numpy.bincount(inverse, weights=Edep * mask_second)

	n_hits        = sum(numpy.bincount(inverse))
	n_hits_prime  = sum(numpy.bincount(inverse, weights=mask_prime))
	n_hits_second = sum(numpy.bincount(inverse, weights=mask_second))
	n_events      = len(event_Edep_total)

	file = ROOT.TFile(args.output_file, "RECREATE")

	histoEdepTotal = ROOT.TH1F("histoEdepTotal", "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)
	for Edep in event_Edep_total:
		histoEdepTotal.Fill(Edep)
	histoEdepTotal.Write()

	histoEdepPrime = ROOT.TH1F("histoEdepPrime", "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)
	for Edep in event_Edep_prime:
		histoEdepPrime.Fill(Edep)
	histoEdepPrime.Write()
 
	histoEdepSecond = ROOT.TH1F("histoEdepSecond", "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)
	for Edep in event_Edep_second:
		histoEdepSecond.Fill(Edep)
	histoEdepSecond.Write()

	file.Close()

	print(f"hits   per event = {n_hits       /n_events:.1f}")
	print(f"hits'  per event = {n_hits_prime /n_events:.1f}")
	print(f"hits'' per event = {n_hits_second/n_events:.1f}")

if __name__ == "__main__":
	main()
