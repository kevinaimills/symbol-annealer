use v5.30;
use warnings;

my $what = 'all*';

my @toProcess = glob $what;
foreach (@toProcess) {
	
	my $name = $_;
	my $con;
	open(my $in, '<', $name) or die $!;

	while(<$in>) {

		m/^(.*) (\d+)/;
		my $num = $2;
		$num *= 500 unless m/^[a-z]\s/;
		s/^(.*) (\d+)/$1 $num/;
		$con .= $_;
	}

	chomp($con);
	
	close $in;
	$name =~ s/Data//;
	open(my $out, '>', "scaled/$name") or die $!;
	select $out;
	print $con;
}
