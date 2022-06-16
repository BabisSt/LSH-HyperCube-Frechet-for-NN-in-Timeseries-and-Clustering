# Finding Nearest Neighbor/s in TimeSeries with Locality Sensitive Hashing, HyperCube, Discrete and Continuous Frechet

Data Clustering Second Project For Software Development for Algorithmic Problems


Used algorithms such as LSH,HyperCube (for first exersize) and Discrete, Continuous Frechet to find NN on TimeSeries with L2.
Plotted my results.
Filtered and reduced complexity and got rid of time dimension.
Applied Discrete and Continuous Frechet between Timeseries.
K-means ++, Lloyd's assignment , assignment by Range Search LSH Frechet / LSH Vector / HyperCube.
Not fully Functional.









2η Εργασία Ανάπτυξη Λογισμικού για Αλγοριθμικά Προβλήματα 

	ΣΤΕΒΗΣ ΧΑΡΑΛΑΜΠΟΣ - ΑΝΤΩΝΙΟΣ sdi1600278
	
Από τι αποτελείται η εργασία:
	Φάκελος assets:	Εκεί θα μπουν τα αρχεία των dataset - query
	Φάκελος bin:		Εκεί μπαίνουν τα εκτελέσιμα
	Φάκελος build:		Εκεί μπαίνουν τα .ο
	Φάκελος include:	Εκεί βρίσκονται τα .h και .hpp
	Φάκελοσ logs:		Εκεί βρίσκεται το αρχείο logs.txt που έχει τις εκτυπώσεις της εργασίας
	Φάκελος src:		Εκεί βρίσκονται τα .cpp
	cluster.conf
	Makefile
	README
	
Πως τρέχει η εργασία:
	Αφού κάνουμε make στην εργασία υπάρχουν δύο τρόποι για να τρέξει. 
	Ο πρώτος είναι να μπούμε στον φάκελο bin και να τρέξουμε τις εντολές όπως λέει η εκφώνηση.
	Ο δεύτερος είναι να τρέξουμε έτοιμες εντολές μέσα από το Makefile όπως για παράδειγμα run-lsh, run-hc. 
	Σε μερικές από αυτές τις εντολές δεν δίνονται όλα τα ορόσματα οπότε η εργασία δίνει τα default.
	
	Αν η εκτέλεση γίνει με τον πρώτο τρόπο τότε η εργασία ζητάει input, query files ενώ αν γίνει με τον δεύτερο
	τρέχει κατευθείαν με τα αρχεία που βρήκε στο Makefile. Στην συνέχεια η εργασία δίνει την δυνατότητα να ξανατρέξει
	με διαφοτερικά στοιχεία.
	
	Τα αποτελέσματα της εργασίας όπως είπαμε παραπάνω βρίσκονται στο αρχείο logs/logs.txt
	
Τι μπορεί να κάνει η εργασία:
	Η εργασία ανοίγει το dataset το διαβάζει και το αποθηκεύει, τόσο για input όσο και για query. 
	Στην συνέχεια λειτουγεί ανάλογα αν είμαστε σε cluster mode ή όχι.
	Αν όχι διαβάζει queries και δημιουργεί lsh ή hypercube ή frechet.
	Σε συνδυασμό με την πρώτη εργασία η δεύτερη εκτελεί σωστά τα πρώτα δύο ερωτήματα, δηλαδή διαβάζει τα dataset και εκτελεί lsh,hypercude 
	όπως στην πρώτη εργασία, είτε κάνει disrcete frechet με νέα distance function.
	Η LSH μπορεί να βρίσκει χρόνους και να κάνει τις απαραίτητες εκτυπώσεις και με brute force και με get closest neighbors.
	Κάνει hash τα data που παίρνει από τα hashtables (θα πούμε παρακάτω), βρίσκει τις g και εκτελεί τα queries.
	H hypercube πέρα από τα παραπάνω δημιουργεί τις f και υπολογίζει τις hamming distances.
	H frechet κάνει snap τις καμπύλες σύμφωνα με το delta που έχει δωθεί. Για το δεύτερο ερώτημα καλούμε την Min_max_filter που βγάζει τα
	duplicates και στην συνέχεια κάνουμε padding για να είναι ίσα τα curves. Τέλος μέσα στην LSH καλούμε την frechet.
	Στο τρίτο ερώτημα κάνουμε filtering , init και padding και είμαστε έτοιμοι να καλέσουμε την continuous frechet.
	Στα hashtables υπολογίζουμε την hashfunction από την τα κομμάτια που αποτελείται και φτίαχνουμε τα tables με τα buckets τους.
	
	Για το Β κομμάτι της εργασίας, διορθώσαμε τα λάθη και πλέον μπορεί να τρέξει κανονικά και να λειτουργήσει όπως απαιτούσε η πρώτη εργασία.
	Επιπλέον τρέχει τους αλγόριθμους Lloyds,LSH με Frechet.
	To cluster κομμάτι της εργασίας τρέχει με τις εντολές run-cluster-...
	
Τι δεν μπορεί να κάνει η εργασία:
	Η εργασία δεν τρέχει για continuous frechet καθώς δεν μπορέσαμε να ενσωματώσουμε την βιβλιοθήκη που μας δώθηκε.


