use v5.30;
use warnings;

my $doCode = 0;
my $doTris = 0;
my $doLetters = 0;
my $outPath = 'out/';


my $what = 'all*.txt';

my @symbols = qw,\\ & | [ ] ( ) ` < > { } ~ _ $ % - / = * + ! @ # . ; : \, ' " ? ^,;
#("a" .. "z", ",", ".", "'", "\"", ";", ":", "?", "!", "(", ")");
my @letters = ("a" .. "z");
my @all = (@symbols, @letters);
@symbols = @all;

my %mgrams;
my %bgrams;
my %tgrams;
my %mgramsLetters;

for (my $i = 0; $i <= $#symbols; $i++) { 
	$mgrams{$symbols[$i]} = 0;
	
	for (my $j = 0; $j <= $#symbols; $j++) {
			
			$bgrams{$symbols[$i] . $symbols[$j]} = 0;
			
			for (my $k = 0; $k <= $#symbols; $k++) {
				$tgrams{$symbols[$i] . $symbols[$j] . $symbols[$k]} = 0;
			}
	}
}

for (my $i = 0; $i <= $#letters; $i++) { 
	$mgramsLetters{$letters[$i]} = 0;
}

# 		my $regex = join "abc", @symbols; # qw,\\ & | ^ [ ] ` < > { } ~ _ $ % - / = * + ! @ # ;,;
# 		my @exclude = qw{. , ? ' " ( )};
		
# 		my $re2 = join "abc", @exclude;

# 		$re2 = quotemeta($re2);
# #		$re2 =~ s/\\\(/\\s/g;
# 		$re2 = "($re2)";
# 		$re2 =~ s/abc/|/g;
		
# 		$regex =~ s/$re2/fmlr/g;
# #		$regex =~ s/.fmlro.//g;
# 		$regex = quotemeta($regex);
# 		$regex = "($regex)";
# 		$regex =~ s/abc/|/g;
# print STDERR $regex;

my @toProcess = glob $what;
foreach (@toProcess) {
	my $p = 1;
	open(my $in, '<', $_) or die $!;
	while(<$in>) {
#		print STDERR "$p - ";
		$p++;
		s/\\\\/\\/;
		my $line = $_;

		# while ( (my $key, my $value) = each %mgrams ) {
		# 	my $qkey = quotemeta($key);
			$mgrams{$1} += $2 if $line =~ /^(.) (\d+)/;
			 #* $mult;
		# }

		# if ($doLetters) {
		# 	while ( (my $key, my $value) = each %mgramsLetters ) {
		# 		my $qkey = quotemeta($key);
		# 		my $lcLine = lc $line;
		# 		my $count = () = $lcLine =~ /$qkey/g;
		# 		$mgramsLetters{$key} += $count; #* $mult;
		# 	}
		# }

		# while ( (my $key, my $value) = each %bgrams ) {
		# 	my $qkey = quotemeta($key);
			$bgrams{$1} += $2 if $line =~ /^(..) (\d+)/;
			$bgrams{$1} += $2 if $line =~ /^('[a-z]) (\d+)/; 
			$bgrams{$1} += $2 if $line =~ /^([a-z]') (\d+)/;
			 #* $mult;
		# }	

		next unless $doTris;
		
		# while ( (my $key, my $value) = each %tgrams ) {
		# 	my $qkey = quotemeta($key);
		# 	my $count = () = $line =~ /$qkey/g;
		# 	$tgrams{$key} += $count; # * $mult;
		# }		
	}

}

my @mgrams = sort by_mgrams keys %mgrams;
my @mgramsLetters = sort by_mgramsLetters keys %mgramsLetters;
my @bgrams = sort by_bgrams keys %bgrams;
my @tgrams = sort by_tgrams keys %tgrams if $doTris;

if ($doLetters) {
	open(my $out, '>', $outPath . "allLetters.txt") or die $!;
	select $out;
	for (my $i = 0; $i <= $#mgramsLetters; $i++) {
		my $key = $mgramsLetters[$i];
		$key =~ s/\\/\\\\/;
		print lc "$key $mgramsLetters{$mgramsLetters[$i]}\n";
	}
	close $out;
}

open(my $out, '>', $outPath . "allChars.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#mgrams; $i++) {
	my $key = $mgrams[$i];
	$key =~ s/\\/\\\\/;
	print lc "$key $mgrams{$mgrams[$i]}\n";
}

close $out;
	
open($out, '>', $outPath . "allDigraphs.txt") or die $!;
select $out;
for (my $i = 0; $i <= $#bgrams; $i++) {
	my $key = $bgrams[$i];
	
	if ($key =~ m/\\\\/) {
		$key =~ s/\\\\/\\\\\\\\/;
	} else {
		$key =~ s/\\/\\\\/;
	}
	
	print lc "$key $bgrams{$bgrams[$i]}\n";
}
close $out;

if ($doTris) {
	open($out, '>', $outPath . "allTrigraphs.txt") or die $!;
	select $out;
	for (my $i = 0; $i <= $#tgrams; $i++) {
		my $key = $tgrams[$i];
		
		if ($key =~ m/\\\\/) {
			$key =~ s/\\\\/\\\\\\\\/;
		} else {
			$key =~ s/\\/\\\\/;
		}

		print lc "$key $tgrams{$tgrams[$i]}\n";
	}
	close $out;
}

sub by_mgrams { $mgrams{$b} <=> $mgrams{$a} }
sub by_mgramsLetters { $mgramsLetters{$b} <=> $mgramsLetters{$a} }
sub by_bgrams { $bgrams{$b} <=> $bgrams{$a} }
sub by_tgrams { $tgrams{$b} <=> $tgrams{$a} }