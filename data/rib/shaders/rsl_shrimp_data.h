#ifndef SHRIMP_DATA_H
#define SHRIMP_DATA_H 1

/* Set of functions and tables with n and n+k data. Schott catalogue data
 * generated with a modified mktables.C from Mario Marengo's VEX glass shader.
 * Other data, n+k, from FreeSnell:
 * http://people.csail.mit.edu/jaffer/FreeSnell/
 * And converted from the Sopra (thin film metrology) database.
 * http://www.sopra-sa.com/index2.php?goto=dl&rub=4
 * note: FreeSnell and Sopra converted n+k data to be added later. */

////////////////////////////////////////////////////////////////////////////////
/* optics */
/* Optical constants for various glasses. These are synced to the "optics"
 * menu - the lookup index is meant to be the value of that menu.
 * The measured quantities come from the Schott catalog, and the data is 
 * sorted in order of increasing dispersion.
 * This function returns the following optical constants:
 * nd - average index of refraction (eta)
 * nspread - IOR delta over the visible range (439nm - 642nm in this
 * implementation)
 * b1,b2,b3, c1,c2,c3 - Sellmeier constants for calculating the dispersion
 * curve.
 * */
/*    "0" "Generic: Crown Glass: [n=1.50, spread=0.010]"
      "1" "Generic: Crystal Quartz: [n=1.54, spread=0.016]"
      "2" "Generic: Light Flint: [n=1.60, spread=0.018]"
      "3" "Generic: Dense Flint: [n=1.75, spread=0.034]"
      "4" "Generic: Diamond: [n=2.42, spread=0.044]"
      "5" "Measured: Flint Crown: N-FK51A"
      "6" "Measured: Phosphate Crown: N-PK52A"
      "7" "Measured: Phosphate Crown: N-PK51"
      "8" "Measured: Flint Crown: N-FK5"
      "9" "Measured: Borosilicate Crown: N-BK10"
      "10" "Measured: Phosphate Crown: P-PK53"
      "11" "Measured: Borosilicate Crown: N-BK7"
      "12" "Measured: Dense Phosphate Crown: N-PSK53"
      "13" "Measured: Dense Phosphate Crown: N-PSK3"
      "14" "Measured: Dense Phosphate Crown: N-PSK53A"
      "15" "Measured: Dense Crown: N-SK5"
      "16" "Measured: Zinc Crown: N-ZK7"
      "17" "Measured: Dense Crown: N-SK11"
      "18" "Measured: Dense Crown: N-SK14"
      "19" "Measured: Crown: K7"
      "20" "Measured: Dense Crown: N-SK16"
      "21" "Measured: Lanthanum Crown: N-LAK21"
      "22" "Measured: Barium Crown: N-BAK2"
      "23" "Measured: Dense Crown: P-SK57"
      "24" "Measured: Crown: N-K5"
      "25" "Measured: Dense Crown: N-SK4"
      "26" "Measured: Lanthanum Crown: N-LAK7"
      "27" "Measured: Dense Crown: N-SK15"
      "28" "Measured: Barium Crown: N-BAK1"
      "29" "Measured: Dense Crown: N-SK2"
      "30" "Measured: Crown: K10"
      "31" "Measured: Barium Crown: N-BAK4"
      "32" "Measured: Lanthanum Crown: N-LAK22"
      "33" "Measured: Lanthanum Crown: N-LAK14"
      "34" "Measured: Lanthanum Crown: N-LAK12"
      "35" "Measured: Lanthanum Crown: N-LAK9"
      "36" "Measured: Lanthanum Crown: N-LAK34"
      "37" "Measured: Short Flint: N-KZFS2"
      "38" "Measured: Barium Light Flint: N-BALF4"
      "39" "Measured: Lanthanum Crown: N-LAK8"
      "40" "Measured: Barium Light Flint: N-BALF5"
      "41" "Measured: Very Dense Crown: N-SSK2"
      "42" "Measured: Lanthanum Crown: N-LAK33A"
      "43" "Measured: Crown/Flint: N-KF9"
      "44" "Measured: Very Dense Crown: N-SSK5"
      "45" "Measured: Lanthanum Crown: N-LAK10"
      "46" "Measured: Very Dense Crown: N-SSK8"
      "47" "Measured: Lanthanum Flint: N-LAF34"
      "48" "Measured: Lanthanum Flint: N-LAF35"
      "49" "Measured: Lanthanum Flint: N-LAF3"
      "50" "Measured: Lanthanum Flint: N-LAF21"
      "51" "Measured: Barium Flint: N-BAF10"
      "52" "Measured: Barium Flint: N-BAF3"
      "53" "Measured: Barium Flint: N-BAF52"
      "54" "Measured: Lanthanum Dense Flint: N-LASF44"
      "55" "Measured: Very Light Flint: LLF1"
      "56" "Measured: Barium Flint: N-BAF51"
      "57" "Measured: Lanthanum Flint: N-LAF2"
      "58" "Measured: Short Flint: N-KZFS4"
      "59" "Measured: Short Flint: KZFSN4"
      "60" "Measured: Lanthanum Flint: N-LAF33"
      "61" "Measured: Barium Flint: N-BAF4"
      "62" "Measured: Lanthanum Dense Flint: N-LASF41"
      "63" "Measured: Short Flint: N-KZFS11"
      "64" "Measured: Lanthanum Flint: N-LAF36"
      "65" "Measured: Lanthanum Dense Flint: P-LASF47"
      "66" "Measured: Light Flint: LF5"
      "67" "Measured: Lanthanum Dense Flint: N-LASF31A"
      "68" "Measured: Lanthanum Dense Flint: N-LASF43"
      "69" "Measured: Short Flint: KZFSN5"
      "70" "Measured: Barium Dense Flint: N-BASF64"
      "71" "Measured: Fluorite Crown: F5"
      "72" "Measured: Lanthanum Dense Flint: N-LASF40"
      "73" "Measured: Fluorite Crown: F4"
      "74" "Measured: Flint: N-F2"
      "75" "Measured: Fluorite Crown: F2"
      "76" "Measured: Short Flint: KZFS12"
      "77" "Measured: Barium Dense Flint: N-BASF2"
      "78" "Measured: Lanthanum Dense Flint: N-LASF45"
      "79" "Measured: Lanthanum Flint: LAFN7"
      "80" "Measured: Lanthanum Flint: N-LAF7"
      "81" "Measured: Short Flint: N-KZFS8"
      "82" "Measured: Dense Flint: SF2"
      "83" "Measured: Dense Flint: N-SF5"
      "84" "Measured: Dense Flint: SF5"
      "85" "Measured: Lanthanum Dense Flint: N-LASF9"
      "86" "Measured: Lanthanum Dense Flint: N-LASF46A"
      "87" "Measured: Dense Flint: N-SF8"
      "88" "Measured: Dense Flint: N-SF64"
      "89" "Measured: Dense Flint: N-SF15"
      "90" "Measured: Dense Flint: SF15"
      "91" "Measured: Dense Flint: N-SF1"
      "92" "Measured: Dense Flint: SF1"
      "93" "Measured: Dense Flint: N-SF10"
      "94" "Measured: Dense Flint: SF10"
      "95" "Measured: Dense Flint: SF4"
      "96" "Measured: Dense Flint: N-SF4"
      "97" "Measured: Dense Flint: N-SF14"
      "98" "Measured: Dense Flint: SF14"
      "99" "Measured: Dense Flint: N-SF56"
      "100" "Measured: Dense Flint: SF56A"
      "101" "Measured: Dense Flint: SF11"
      "102" "Measured: Dense Flint: N-SF11"
      "103" "Measured: Dense Flint: SF6HT"
      "104" "Measured: Dense Flint: SF6"
      "105" "Measured: Dense Flint: N-SF6"
      "106" "Measured: Dense Flint: N-SF6HT"
      "107" "Measured: Dense Flint: SF57"
      "108" "Measured: Dense Flint: SF57HHT"
      "109" "Measured: Dense Flint: N-SF57"
      "110" "Measured: Dense Flint: N-SF57HT"
      "111" "Measured: Dense Flint: N-SF66"
      "112" "Measured: Dense Flint: SF66"
	  */

// Glass ior table for RYGCBV
void
etaTableRYGCBV(
				uniform float model; // [0,112] range
				output uniform float eta[6];
		)
{
	uniform float glassior[678] =
	{
		1.495, 1.497, 1.499, 1.501, 1.503, 1.505,
		1.532, 1.5352, 1.5384, 1.5416, 1.5448, 1.548,
		1.591, 1.5946, 1.5982, 1.6018, 1.6054, 1.609,
		1.733, 1.7398, 1.7466, 1.7534, 1.7602, 1.767,
		2.391, 2.4026, 2.4142, 2.4258, 2.4374, 2.449,
		1.48512, 1.48679, 1.48859, 1.49031, 1.49179, 1.49342,
		1.49548, 1.49724, 1.49915, 1.50097, 1.50254, 1.50426,
		1.52685, 1.52883, 1.53098, 1.53303, 1.53481, 1.53676,
		1.48574, 1.48777, 1.48993, 1.49197, 1.49373, 1.49566,
		1.49595, 1.49812, 1.50044, 1.50264, 1.50453, 1.50661,
		1.52492, 1.52722, 1.52971, 1.53208, 1.53415, 1.53642,
		1.51478, 1.51712, 1.51964, 1.52203, 1.5241, 1.52637,
		1.61771, 1.62053, 1.62359, 1.62651, 1.62905, 1.63184,
		1.55014, 1.55267, 1.55539, 1.55798, 1.56022, 1.56268,
		1.61558, 1.61839, 1.62144, 1.62436, 1.62689, 1.62968,
		1.58673, 1.58951, 1.59252, 1.59539, 1.59788, 1.60062,
		1.50639, 1.5088, 1.5114, 1.51387, 1.51601, 1.51836,
		1.56153, 1.56421, 1.56711, 1.56988, 1.57228, 1.57493,
		1.60063, 1.60351, 1.60662, 1.6096, 1.61218, 1.61502,
		1.50902, 1.51146, 1.51411, 1.51663, 1.51883, 1.52125,
		1.61785, 1.62082, 1.62404, 1.62711, 1.62977, 1.63271,
		1.63784, 1.64092, 1.64425, 1.64744, 1.6502, 1.65324,
		1.53771, 1.54032, 1.54315, 1.54586, 1.54821, 1.55081,
		1.58455, 1.58739, 1.59047, 1.59341, 1.59597, 1.59878,
		1.52031, 1.52284, 1.52559, 1.52822, 1.5305, 1.53302,
		1.61012, 1.61313, 1.61641, 1.61954, 1.62226, 1.62526,
		1.64883, 1.65204, 1.65553, 1.65886, 1.66175, 1.66495,
		1.6203, 1.62339, 1.62675, 1.62997, 1.63277, 1.63586,
		1.57004, 1.5729, 1.57601, 1.579, 1.5816, 1.58448,
		1.60473, 1.60781, 1.61117, 1.61439, 1.61719, 1.6203,
		1.49917, 1.50172, 1.50451, 1.50717, 1.50949, 1.51207,
		1.56631, 1.56923, 1.57241, 1.57547, 1.57813, 1.58107,
		1.64825, 1.65159, 1.65524, 1.65874, 1.66178, 1.66515,
		1.69367, 1.6973, 1.70124, 1.70499, 1.70826, 1.71186,
		1.67487, 1.67839, 1.68224, 1.68593, 1.68915, 1.69271,
		1.68786, 1.6915, 1.69546, 1.69924, 1.70253, 1.70616,
		1.72584, 1.72969, 1.73388, 1.73789, 1.74137, 1.74521,
		1.55578, 1.55877, 1.562, 1.56508, 1.56776, 1.57072,
		1.57691, 1.57999, 1.58336, 1.5866, 1.58943, 1.59257,
		1.70971, 1.71353, 1.71768, 1.72164, 1.72509, 1.7289,
		1.54487, 1.54779, 1.55099, 1.55406, 1.55675, 1.55974,
		1.61941, 1.62276, 1.62642, 1.62994, 1.63301, 1.63643,
		1.75036, 1.7545, 1.75902, 1.76335, 1.76712, 1.77129,
		1.52096, 1.52386, 1.52704, 1.53011, 1.53279, 1.53578,
		1.65526, 1.65895, 1.66301, 1.66692, 1.67035, 1.67417,
		1.71651, 1.72059, 1.72505, 1.72932, 1.73306, 1.73721,
		1.61469, 1.61822, 1.6221, 1.62586, 1.62915, 1.63283,
		1.76866, 1.77312, 1.77799, 1.78268, 1.78678, 1.79132,
		1.73959, 1.7439, 1.74861, 1.75314, 1.75711, 1.7615,
		1.71334, 1.71759, 1.72227, 1.72681, 1.73079, 1.73522,
		1.78392, 1.78866, 1.79386, 1.79887, 1.80325, 1.80813,
		1.66655, 1.67059, 1.67505, 1.67937, 1.68317, 1.68741,
		1.57967, 1.58322, 1.58713, 1.59093, 1.59428, 1.59804,
		1.60544, 1.60915, 1.61324, 1.61721, 1.62072, 1.62465,
		1.79996, 1.80488, 1.8103, 1.81554, 1.82012, 1.82522,
		1.54522, 1.54861, 1.55237, 1.55601, 1.55922, 1.56282,
		1.64871, 1.65281, 1.65736, 1.66178, 1.66568, 1.67004,
		1.73993, 1.74463, 1.74983, 1.75488, 1.75932, 1.7643,
		1.60997, 1.61391, 1.61822, 1.62239, 1.62605, 1.63013,
		1.61, 1.61395, 1.61828, 1.62247, 1.62616, 1.63027,
		1.78147, 1.78653, 1.79212, 1.79754, 1.8023, 1.80762,
		1.60232, 1.60623, 1.61057, 1.6148, 1.61854, 1.62276,
		1.83028, 1.83577, 1.84184, 1.84773, 1.8529, 1.85867,
		1.63406, 1.63834, 1.64305, 1.64761, 1.65161, 1.65608,
		1.79492, 1.80026, 1.80618, 1.81192, 1.81699, 1.82265,
		1.8013, 1.80688, 1.81305, 1.81906, 1.82436, 1.83028,
		1.57799, 1.582, 1.58646, 1.59082, 1.59468, 1.59903,
		1.87773, 1.88385, 1.89065, 1.89725, 1.90308, 1.90958,
		1.80127, 1.80688, 1.8131, 1.81916, 1.82451, 1.83052,
		1.6501, 1.65477, 1.65994, 1.66497, 1.66941, 1.67441,
		1.69968, 1.7047, 1.7103, 1.71578, 1.72065, 1.72613,
		1.59959, 1.60404, 1.60902, 1.61389, 1.61823, 1.62311,
		1.82865, 1.83492, 1.84193, 1.8488, 1.8549, 1.86178,
		1.61254, 1.61725, 1.62253, 1.62771, 1.63233, 1.63754,
		1.61596, 1.62072, 1.62605, 1.6313, 1.63599, 1.64133,
		1.61594, 1.62071, 1.62605, 1.6313, 1.63598, 1.64127,
		1.69136, 1.69675, 1.70276, 1.70864, 1.71386, 1.71975,
		1.66003, 1.66518, 1.67096, 1.67667, 1.68176, 1.68756,
		1.79557, 1.80197, 1.80915, 1.81622, 1.82252, 1.82967,
		1.74434, 1.75034, 1.75706, 1.76366, 1.76954, 1.77619,
		1.74434, 1.75034, 1.75708, 1.76374, 1.76969, 1.77645,
		1.71547, 1.72128, 1.72779, 1.73418, 1.73988, 1.74632,
		1.64311, 1.64844, 1.65444, 1.66035, 1.66564, 1.67164,
		1.66773, 1.67352, 1.68005, 1.68653, 1.69236, 1.69902,
		1.66771, 1.67351, 1.68006, 1.68653, 1.69233, 1.69892,
		1.84394, 1.85128, 1.85957, 1.86777, 1.87512, 1.88348,
		1.89678, 1.90478, 1.91383, 1.92279, 1.93083, 1.93999,
		1.6837, 1.68979, 1.69669, 1.70353, 1.70969, 1.71674,
		1.70036, 1.70682, 1.71413, 1.72141, 1.72797, 1.73549,
		1.69342, 1.69982, 1.70707, 1.71428, 1.72079, 1.72826,
		1.69343, 1.69986, 1.70714, 1.71438, 1.7209, 1.72834,
		1.71161, 1.7183, 1.72589, 1.73344, 1.74026, 1.74807,
		1.71158, 1.71831, 1.72593, 1.73349, 1.7403, 1.74806,
		1.72223, 1.72927, 1.73726, 1.74524, 1.75245, 1.76073,
		1.72218, 1.72925, 1.73728, 1.74529, 1.75251, 1.76079,
		1.74872, 1.75626, 1.76485, 1.77341, 1.78112, 1.78995,
		1.74861, 1.7562, 1.76484, 1.77348, 1.7813, 1.79029,
		1.75505, 1.76293, 1.77193, 1.78093, 1.7891, 1.79851,
		1.75505, 1.76293, 1.77193, 1.78095, 1.78912, 1.79853,
		1.77762, 1.78587, 1.79529, 1.80473, 1.8133, 1.82318,
		1.7776, 1.78587, 1.7953, 1.80474, 1.81328, 1.82309,
		1.77755, 1.7859, 1.79545, 1.80502, 1.81372, 1.82374,
		1.77753, 1.7859, 1.79547, 1.80508, 1.8138, 1.82388,
		1.79772, 1.80641, 1.81633, 1.82627, 1.83526, 1.84559,
		1.79772, 1.80641, 1.81633, 1.82627, 1.83526, 1.84559,
		1.79771, 1.80641, 1.81635, 1.82634, 1.8354, 1.84587,
		1.79771, 1.80641, 1.81635, 1.82634, 1.8354, 1.84587,
		1.83832, 1.84804, 1.85918, 1.87037, 1.88053, 1.89225,
		1.83832, 1.84804, 1.85918, 1.87037, 1.88053, 1.89225,
		1.83832, 1.84803, 1.85918, 1.87042, 1.88066, 1.89252,
		1.83832, 1.84803, 1.85918, 1.87042, 1.88066, 1.89252,
		1.91261, 1.92455, 1.93838, 1.95246, 1.96543, 1.98064,
		1.91257, 1.92456, 1.93841, 1.95242, 1.96523, 1.98014
		};
	
	uniform float i;
	for (i = 0; i < 6; i += 1) {
		eta[i] = glassior[6 * model + i];
	}
}

////////////////////////////////////////////////////////////////////////////////
#endif /* SHRIMP_DATA_H */

