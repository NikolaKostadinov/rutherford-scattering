import sys
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
	parser.add_argument("-z", "--thickness",    type=float, default=0.5,                     help="detector thickness in mm")
	parser.add_argument("-c", "--z-bins",       type=int,   default=1000,                    help="number of bins for penetration histogram")
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
	hits_data = dataframe.AsNumpy([ "EventID", "Edep_keV", "ParentTrackID", "X_mm", "Y_mm", "Z_mm" ])

	eventID   = hits_data["EventID"]
	Edep      = hits_data["Edep_keV"]
	parentID  = hits_data["ParentTrackID"]
	z         = hits_data["Z_mm"]

	z_shifted = z + args.thickness/2

	unique_eventID, inverse = numpy.unique(eventID, return_inverse=True)

	mask_prime  = parentID == args.prime_parent
	mask_second = parentID >  args.prime_parent

	event_Edep_total  = numpy.bincount(inverse, weights=Edep              )
	event_Edep_prime  = numpy.bincount(inverse, weights=Edep * mask_prime )
	event_Edep_second = numpy.bincount(inverse, weights=Edep * mask_second)
	
	event_max_z_total  = numpy.full(unique_eventID.shape, -numpy.inf)
	event_max_z_prime  = numpy.full(unique_eventID.shape, -numpy.inf)
	event_max_z_second = numpy.full(unique_eventID.shape, -numpy.inf)
	numpy.maximum.at(event_max_z_total,  inverse, z_shifted)
	numpy.maximum.at(event_max_z_prime,  inverse, numpy.where(mask_prime,  z_shifted, -numpy.inf))
	numpy.maximum.at(event_max_z_second, inverse, numpy.where(mask_second, z_shifted, -numpy.inf))
	
	n_hits        = sum(numpy.bincount(inverse, weights=None       ))
	n_hits_prime  = sum(numpy.bincount(inverse, weights=mask_prime ))
	n_hits_second = sum(numpy.bincount(inverse, weights=mask_second))
	n_events      = len(event_Edep_total)

	file = ROOT.TFile(args.output_file, "RECREATE")

	histoEdepTotal  = ROOT.TH1F("histoEdepTotal",  "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)
	histoEdepPrime  = ROOT.TH1F("histoEdepPrime",  "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)
	histoEdepSecond = ROOT.TH1F("histoEdepSecond", "Total Energy Deposit per Event;Edep [keV];Counts", args.e_bins, args.e_min, args.e_max)	
	histoMaxZTotal  = ROOT.TH1F("histoMaxZTotal",  "Penetration per event;max z [mm];Counts", args.z_bins, 0, args.thickness)
	histoMaxZPrime  = ROOT.TH1F("histoMaxZPrime",  "Penetration per event;max z [mm];Counts", args.z_bins, 0, args.thickness)
	histoMaxZSecond = ROOT.TH1F("histoMaxZSecond", "Penetration per event;max z [mm];Counts", args.z_bins, 0, args.thickness)

	[ histoEdepTotal.Fill(Edep)   for Edep  in event_Edep_total   ]
	[ histoEdepPrime.Fill(Edep)   for Edep  in event_Edep_prime   ]
	[ histoEdepSecond.Fill(Edep)  for Edep  in event_Edep_second  ]
	[ histoMaxZTotal.Fill(max_z)  for max_z in event_max_z_total  ]
	[ histoMaxZPrime.Fill(max_z)  for max_z in event_max_z_prime  ]
	[ histoMaxZSecond.Fill(max_z) for max_z in event_max_z_second ]
	
	histoMaxZTotal.Write()
	histoMaxZPrime.Write()
	histoMaxZSecond.Write()
	histoEdepTotal.Write()
	histoEdepPrime.Write()
	histoEdepSecond.Write()

	file.Close()

	print(f"hits   per event = {n_hits       /n_events:.1f}")
	print(f"hits'  per event = {n_hits_prime /n_events:.1f}")
	print(f"hits'' per event = {n_hits_second/n_events:.1f}")

if __name__ == "__main__":
	try:
		main()
	except KeyboardInterrupt:
		sys.exit(0)
