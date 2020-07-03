inlets = 1;
outlets = 2;

function list()
{
	var a = arrayfromargs(arguments);
	var crc = calcCRC(a[0], a[1]);
	
	if(crc === a[2]){
		outlet(0, "id", a[0]);	
		outlet(0, "val", a[1]);
	} else {
		outlet(1, "bang");
	}
}

function calcCRC(val1, val2){
	var bArr1 = longToByteArray(val1);
	var bArr2 = longToByteArray(val2);
	
	var byteArray = bArr1.concat(bArr2);
	var result = 0xffff;
	for(var i = 0; i < byteArray.length; i ++) {
		result ^= byteArray[i];
		for(var j = 0; j < 8; j++){
			if(result & 0x01){
				result = (result >> 1) ^ 0xA001;
			} else {
				result >>= 1;
			}
		}
	}
	return result;
}

function longToByteArray(long) {
    // we want to represent the input as a 8-bytes array
    var byteArray = [0, 0, 0, 0, 0, 0, 0, 0];

    for ( var index = 0; index < byteArray.length; index ++ ) {
        var byte = long & 0xff;
        byteArray [ index ] = byte;
        long = (long - byte) / 256 ;
    }
	byteArray = byteArray.slice(0, 2);
	byteArray.reverse();
    return byteArray;
}