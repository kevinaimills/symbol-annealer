use v5.30;
use warnings;
use Getopt::Std;
use List::Util qw( min max );

my $doTris = 0;
my $doPunc = 1;
my $doLetters = 1;
my $scaleToMatchText = 1;
my $codeToTextRatio = 0.1; # 0.1
my $mergeCodeAndText = 1;
my $overwriteMainProgramData = 1;
my $constructSnakeCaseData = 1;
my $snakeCaseScale = 1;


my $closeParenScale = 0.5; # 0.5
my $closeQuoteScale = $closeParenScale;
my $contractionScale = 1;

my %adhocScaleMons = (
	# 'u', => 0.9,
	'+' => 2,
	')' => 0.9,
	'}' => $closeParenScale,
	']' => $closeParenScale,
	'\\' => 3,
	# '"' => 0.5,
);

my %adhocScaleBis = (
	# '\'\''  => $closeQuoteScale,
	# '""'  => $closeQuoteScale,
	'==' => 3,
	# '$_' => 2,
	');' => 0.1,
	# 'cd' => 5,
	# 'kn' => 4,
	# 'mp' => 2,
	'my' => 2,
	'ny' => 2,
	# 'if' => 2,
	'ey' => 4, 
	'yo' => 4,
	'ok' => 4,
	'\'r' => 3,
	'\'l' => 3,
	'\'d' => 2,
	'\'m' => 2,
	'\'v' => 2,
	'i\'' => 5,
	'u\'' => 5,
	# '^\\' => 0,
	# '^?' => 0,
	# '\\^' => 0,
	# '?^' => 0,
	# '^^' => 0,
	# '\"r' => 0.1, 
	# 'o.' => 0.1,
	# 'hu' => 4,
	# '=~' => 10,
	# '(|' => 3, 
	# '\'t' => $contractionScale,
	# '\'d' => $contractionScale,
	# '\'l' => $contractionScale,
	# '\'m' => $contractionScale,
	# '\'v' => $contractionScale,
	# '\'r' => $contractionScale,
	# 'n\'' => $contractionScale,
	# 'i\'' => $contractionScale,
	# 't\'' => $contractionScale,
	# 'e\'' => $contractionScale,
	# 'y\'' => $contractionScale,
	# 'o\'' => $contractionScale,
	# 'u\'' => $contractionScale,
);

my %adhocScaleTris = (
	'you' => 2,
);

my %adhocScaleRegEx = ( # slow, and make sure to escape properly (these are concatenated as-is into a regex)
	# 'th' => 0,
	'"[a-z]' => 0.5,
	'[a-z]"' => 0.5,
	'[a-z,\.?!]"' => 0.1,
);

while ( (my $key, my $value) = each %adhocScaleRegEx ) {
	delete $adhocScaleRegEx{$key} unless $value != 1;
}

# while ( (my $key, my $value) = each %adhocScaleRegEx ) {
# 	print "$key $value";
# }

# my $adhocDownScaleFactor = 0.1; # multiplier
# my @adhocDownScaleSymbols = qw/ ) } ] /;
our $opt_a = 1; # create output that merges all selected languages together 
our $opt_n = 1; # normalize data so volume of code analyzed per language is irrelevant
our $opt_s = 1; # scale data so some languages are treated as more important than others
#getopts('ans');

# absolute values irrelevant if normalize is enabled (relative values still matter)
my %languageScales = (
	'c'  => 100,
	'sh' => 25,
	'rs' => 100,
	'pl' => 25,
	'py' => 100,
	'cs' => 100,
	'ts' => 100,
	'go' => 25,
);

# my %languageScales = (
# 	'c'  => 100,
# 	'sh' => 25,
# 	'rs' => 100,
# 	'pl' => 50,
# 	'py' => 100,
# 	'cs' => 100,
# 	'ts' => 100,
# 	'go' => 50,
# );

my $inPath = './out/';
my $outPath = './mergedByLan/';
$outPath = './mergedAll/' if ($opt_a);
$outPath = '../data/' if ($opt_a && $overwriteMainProgramData);

# my @languages = qw( c h go bash sh rs pl pm py cs ts );
my %sameLan;
my $lan;
my $lanEq;
my @languages;
while ( ($lan, $lanEq) = each %languageScales ) { 
	push @languages, $lan;
}
$sameLan{'h'} = 'c';
$sameLan{'pm'} = 'pl';
$sameLan{'bash'} = 'sh';


while ( ($lan, $lanEq) = each %sameLan ) {
	push @languages, $lan;
	if (exists $languageScales{$lan}) {
		$languageScales{$lanEq} = $languageScales{$lan}
	} else {
		$languageScales{$lan} = $languageScales{$lanEq}
	}
}

my @dataTypes = qw( Chars Digraphs Letters Trigraphs );
# my @dataTypes = qw( Chars );
my %charsPerLan;
my %scaleFactors;
$charsPerLan{$_} = 0 foreach(@languages);


# for (my $i = 0; $i <= $#charsPerLan; $i++) {
# 	$charsPerLan[$i] = 0;
# }

my @languagesRef = @languages;
# @languages = ( "" ) if $opt_a;

my @symbols = qw,\\ & | [ ] ( ) ` < > { } ~ _ $ % - / = * + ! @ # . ; : \, ' " ? ^,;
#("a" .. "z", ",", ".", "'", "\"", ";", ":", "?", "!", "(", ")");
my @letters = ("a" .. "z");

#my @all = (@symbols, @letters);
#@symbols = @all;

my %mgrams;
my %bgrams;
my %tgrams;
my %mgramsLetters;
my %mgramsText;
my %bgramsText;
my %tgramsText;

my $currentDataType;
my $numChars;

if ($opt_n) {

	while ( ($lan, $numChars) = each %charsPerLan ) {	
		my $ucLan = uc $lan;
		my @toScale = glob "${inPath}allChars$ucLan*.txt"; 

		foreach (@toScale) {
#			print;
			open(my $in, '<', $_) or die $!;
			while(<$in>) {
				s/\\\\/\\/;
				my $line = $_;
				$charsPerLan{$lan} += $2 if $line =~ /^(.) (\d+)/; 
			}
		}
	}
	
	while ( ($lan, $numChars) = each %charsPerLan ) {	
		$charsPerLan{$sameLan{$lan}} += $charsPerLan{$lan} if exists $sameLan{$lan};
		$charsPerLan{$lan} = 0 if exists $sameLan{$lan};
	}

	my $max = max %charsPerLan;
	while ( ($lan, $numChars) = each %charsPerLan ) {	
		$scaleFactors{$lan} = $max / $numChars if $numChars;
	}

	while ( ($lan, $numChars) = each %charsPerLan ) {	
		$scaleFactors{$lan} = $scaleFactors{$sameLan{$lan}} if exists $sameLan{$lan};
	}	
	# print "\n";
	# print "$_ \n" foreach(%scaleFactors); 
}

&initVars if $opt_a;

for(my $i = 0; $i <= $#dataTypes; $i++) {
	$currentDataType = $dataTypes[$i];
	for(my $j = 0; $j <= $#languages; $j++) {
		&initVars unless $opt_a;
		$lan = uc $languages[$j];
		my @toMerge = glob "${inPath}all$dataTypes[$i]$lan*.txt"; 
		my $mult = 1;
		$mult = $scaleFactors{$languages[$j]} if exists $scaleFactors{$languages[$j]};
		$mult *= $languageScales{$languages[$j]} if $languageScales{$languages[$j]} && $opt_s;
		# $mult *= $scaleToMatchText if $opt_a && $opt_n
		#		print STDERR "${inPath}all$dataTypes[$i]$lan*.txt"; 

		foreach (@toMerge) {
			open(my $in, '<', $_) or die $!;
			my $fileName = $_;
			while(<$in>) {
				s/\\\\/\\/;
				my $line = $_;
#				print STDERR "\n$mult";
				# my $base = 0;
				# $base = $2 if $line =~ /^(.) (\d+)/; 
				# $base = $2 if $line =~ /^(..) (\d+)/;

#				$bgrams{$1} += ($2 * $mult) if $line =~ /^(..) (\d+)/;
				# my $temp = $2 * $mult;
				# print STDERR "$1 :: $2\n" if $line =~ /^(.) (\d+)/ && $lan eq "PY";
				# print STDERR "$1 :: $2 * $mult\n" if $line =~ /^(.) (\d+)/ && $lan eq "PY";
				# print STDERR "$1 :: $temp\n" if $line =~ /^(.) (\d+)/ && $lan eq "PY";

				$mgrams{$1} += $2 * $mult if $line =~ /^([^a-zA-Z]) (\d+)/; 
				$mgramsLetters{$1} += $2 * $mult if $line =~ /^([a-zA-Z]) (\d+)/; 
				$bgrams{$1} += $2 * $mult if $line =~ /^(..) (\d+)/; 
#				$bgrams{$1} += $2 if $line =~ /^([a-z]') (\d+)/;

#				next unless $doTris;
				
			}

		}

		&writeData unless $opt_a;
	}
}

if ($scaleToMatchText && $opt_a) {
	my $numLetters = 0;
	my $puncLetters = 0;
	my $totalSymbols = 0;
	my $key;
	my $value;
	my $key2;
	my $value2;

	open(my $in, '<', 'textData/allChars.txt') or die $!;
	while(<$in>) {
		my $line = $_;
		$numLetters += $2 if $line =~ /^([a-zA-Z]) (\d+)/; 
	}
	
	while ( ($key, $value) = each %mgrams ) {
		$totalSymbols += $value;
	}

	my $scale = ($numLetters / $totalSymbols) * $codeToTextRatio;
	# print STDERR $scale;
	while ( ($key, $value) = each %bgrams ) {
		$bgrams{$key} *= $scale;
		# print STDERR "$scale\n";
		# print STDERR "$scale :: $key :: $bgrams{$key} :: $value\n";
	}

	while ( ($key, $value) = each %mgrams ) {
		$mgrams{$key} *= $scale;
		# print STDERR "$scale :: $key :: $mgrams{$key}\n";
	}

	while ( ($key, $value) = each %adhocScaleMons ) {
		$mgrams{$key} *= $value;
	}

	while ( ($key, $value) = each %adhocScaleBis ) {
		$bgrams{$key} *= $value;
	}

	if ($mergeCodeAndText) {
		open(my $in, '<', './textData/allChars.txt') or die $!;
		while(<$in>) {
			if (/^(.) (\d+)/) {
				my $mult = exists $adhocScaleMons{$1} ? $adhocScaleMons{$1} : 1; 
				$mgrams{$1} += $2 * $mult;  
				$mgramsText{$1} += $2 * $mult;  
			}
		}		
		
		open(my $in, '<', './textData/allDigraphs.txt') or die $!;
		while(<$in>) {
			if (/^(..) (\d+)/) {
				my $mult = exists $adhocScaleBis{$1} ? $adhocScaleBis{$1} : 1; 
				$bgrams{$1} += $2 * $mult;  
				$bgramsText{$1} += $2 * $mult;  
			}
		}	

		open(my $in, '<', './textData/allTrigraphs.txt') or die $!;
		while(<$in>) {
			if (/^(...) (\d+)/) {
				my $mult = exists $adhocScaleTris{$1} ? $adhocScaleTris{$1} : 1; 
				$tgrams{$1} += $2 * $mult if ($doTris);  
				$tgramsText{$1} += $2 * $mult; 
			}
		}	

		if ($doPunc) {

			open(my $in, '<', './puncData/allChars.txt') or die $!;
			while(<$in>) {
				if (/^[a-z] (\d+)/) {
					$puncLetters += $1;  
				}
			}		

			my $puncScale = $numLetters / $puncLetters;

			open(my $in, '<', './puncData/allChars.txt') or die $!;
			while(<$in>) {
				if (/^(.) (\d+)/) {
					my $mult = exists $adhocScaleMons{$1} ? $adhocScaleMons{$1} : 1; 
					$mgrams{$1} += $2 * $mult * $puncScale;  
					$mgramsText{$1} += $2 * $mult * $puncScale;  
				}
			}		
			
			open(my $in, '<', './puncData/allDigraphs.txt') or die $!;
			while(<$in>) {
				if (/^(..) (\d+)/) {
					my $mult = exists $adhocScaleBis{$1} ? $adhocScaleBis{$1} : 1; 
					$bgrams{$1} += $2 * $mult * $puncScale;  
					$bgramsText{$1} += $2 * $mult * $puncScale;  
				}
			}				
		}
	}

	if ($constructSnakeCaseData) {
#		print STDERR "foo";
		my $totalFirst = 0;
		my $totalLast = 0;
		my $snakeUseLetters = $mgrams{"_"};
		my %eachFirst;
		my %eachLast;

#		print STDERR "in$snakeUseLetters";
#		print STDERR "\n";
		while ( ($key, $value) = each %bgrams ) {
			$snakeUseLetters -= $value if $key =~ /_/;
 		}
#		print STDERR "out$snakeUseLetters";

		open(my $in, '<', './raw/allFirst.txt') or die $!;
		while(<$in>) {
			if (/^([a-z]) (\d+)/) {
				$totalFirst += $2; 
				$eachFirst{$1} = $2;  
			}
		}		

		open(my $in, '<', './raw/allLast.txt') or die $!;
		while(<$in>) {
			if (/^([a-z]) (\d+)/) {
				$totalLast += $2;  
				$eachLast{$1} = $2;  
			}
		}		

		my $c1 = 0;
		my $c2 = 0;

		foreach (@letters) {
			my $snakeFirstBase = $eachFirst{$_} / $totalFirst;
			my $snakeLastBase = $eachLast{$_} / $totalLast;
			$c1 += $snakeFirstBase;
			$c2 += $snakeLastBase;
			my $preSnake = "_$_";
			my $postSnake = $_ . "_";
			$bgrams{$preSnake} = $snakeFirstBase * $snakeUseLetters * $snakeCaseScale / 2;
			$bgrams{$postSnake} = $snakeLastBase * $snakeUseLetters * $snakeCaseScale / 2;
		}

#		print STDERR $c1;
#		print STDERR $c2;
#		print STDERR "bar";
				
		# while ( ($key, $value) = each %mgrams ) {
		# 	next unless $key =~ /[a-z]/;
		# 	my $snakeScaleBase = $value / $numLetters;
		# 	print "\n$snakeScaleBase";
		# 	my $preSnake = "_$key";
		# 	my $postSnake = $key . "_";
		# 	$bgrams{$preSnake} = $snakeScaleBase * $snakeCaseScale / 2;
		# 	$bgrams{$postSnake} = $snakeScaleBase * $snakeCaseScale / 2;
		# }
	}

	while ( ($key, $value) = each %adhocScaleRegEx ) {
		while ( ($key2, $value2) = each %mgrams ) {
			$mgrams{$key2} = $value * $value2 if ($key2 =~ /^$key$/);
		}
		while ( ($key2, $value2) = each %bgrams ) {
			$bgrams{$key2} = $value * $value2 if ($key2 =~ /^$key$/);
		}
		while ( ($key2, $value2) = each %tgrams ) {
			$tgrams{$key2} = $value * $value2 if ($key2 =~ /^$key$/);
		}	
	}
}

$lan = "" if $opt_a;
&writeData if $opt_a;


sub by_mgramsLetters { $mgramsLetters{$b} <=> $mgramsLetters{$a} }
sub by_mgrams { $mgrams{$b} <=> $mgrams{$a} }
sub by_bgrams { $bgrams{$b} <=> $bgrams{$a} }
sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }
sub by_mgramsText { $mgramsText{$b} <=> $mgramsText{$a} }
sub by_bgramsText { $bgramsText{$b} <=> $bgramsText{$a} }
sub by_tgramsText { $tgramsText{$b} <=> $tgramsText{$a} }

sub initVars {
	for (my $i = 0; $i <= $#symbols; $i++) { 
		$mgrams{$symbols[$i]} = 0;
		
		for (my $j = 0; $j <= $#symbols; $j++) {
				
				$bgrams{$symbols[$i] . $symbols[$j]} = 0;

				if ($doTris) {
					for (my $k = 0; $k <= $#symbols; $k++) {
						$tgrams{$symbols[$i] . $symbols[$j] . $symbols[$k]} = 0;
					}
				}
		}
	}

	for (my $i = 0; $i <= $#letters; $i++) { 
		$mgramsLetters{$letters[$i]} = 0;
	}
}

sub writeData {
	my @mgramsLetters = sort by_mgramsLetters keys %mgramsLetters;
	my @mgrams = sort by_mgrams keys %mgrams;
	my @bgrams = sort by_bgrams keys %bgrams;
	my @tgrams = sort by_tgrams keys %tgrams if $doTris;
	my @mgramsText = sort by_mgramsText keys %mgramsText;
	my @bgramsText = sort by_bgramsText keys %bgramsText;
	my @tgramsText = sort by_tgramsText keys %tgramsText;
	my $out;

	if (($currentDataType eq "Letters" || $opt_a) && $doLetters) {
		open(my $out, '>', $outPath . "allLetters$lan.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#mgramsLetters; $i++) {
			my $key = $mgramsLetters[$i];
			my $value = ($mgramsLetters{$mgramsLetters[$i]});
			$key =~ s/\\/\\\\/;
			print lc "$key $value\n";
		}
		close $out;
	}
	
	if ($currentDataType eq "Chars" || $opt_a) {
		open(my $out, '>', $outPath . "allChars$lan.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#mgrams; $i++) {
			my $key = $mgrams[$i];
			my $value = int($mgrams{$mgrams[$i]});
			$key =~ s/\\/\\\\/;
			print lc "$key $value\n";
		}
		close $out;
	}

	if ($currentDataType eq "Digraphs" || $opt_a) {
		open($out, '>', $outPath . "allDigraphs$lan.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#bgrams; $i++) {
			my $key = $bgrams[$i]; 
			my $value = int($bgrams{$bgrams[$i]});
			
			if ($key =~ m/\\\\/) {
				$key =~ s/\\\\/\\\\\\\\/;
			} else {
				$key =~ s/\\/\\\\/;
			}
			
			print lc "$key $value\n";
		}
		close $out;
	}

	if (($currentDataType eq "Trigraphs" || $opt_a) && $doTris) {
		# open($out, '>', $outPath . "allTrigraphs$lan.txt") or die $!;
		# select $out;
		# for (my $i = 0; $i <= $#tgrams; $i++) {
		# 	my $key = $tgrams[$i];
		# 	my $value = int($tgrams{$tgrams[$i]});
		# 	if ($key =~ m/\\\\/) {
		# 		$key =~ s/\\\\/\\\\\\\\/;
		# 	} else {
		# 		$key =~ s/\\/\\\\/;
		# 	}

		# 	print lc "$key $value\n";
		# }
		# close $out;
	}

	if ($opt_a) {		
		open(my $out, '>', $outPath . "textOnly/allChars.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#mgramsText; $i++) {
			my $key = $mgramsText[$i];
			my $value = int($mgramsText{$mgramsText[$i]});
			$key =~ s/\\/\\\\/;
			print lc "$key $value\n";
		}
		close $out;

		open($out, '>', $outPath . "textOnly/allDigraphs.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#bgramsText; $i++) {
			my $key = $bgramsText[$i]; 
			my $value = int($bgramsText{$bgramsText[$i]});
			
			if ($key =~ m/\\\\/) {
				$key =~ s/\\\\/\\\\\\\\/;
			} else {
				$key =~ s/\\/\\\\/;
			}
			
			print lc "$key $value\n";
		}
		close $out;

		open($out, '>', $outPath . "textOnly/allTrigraphs.txt") or die $!;
		select $out;
		for (my $i = 0; $i <= $#tgramsText; $i++) {
			my $key = $tgramsText[$i];
			my $value = int($tgramsText{$tgramsText[$i]});
			if ($key =~ m/\\\\/) {
				$key =~ s/\\\\/\\\\\\\\/;
			} else {
				$key =~ s/\\/\\\\/;
			}

			print lc "$key $value\n";
		}
		close $out;
	}
}