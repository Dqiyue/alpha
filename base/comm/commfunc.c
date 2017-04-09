/**
 * 
 * @author:          kylin
 * @email:            dqiyue@foxmail.com
 * @dateTime:     2017-04-11 Tue 17:39:40
 * @description: 
 * 
 */


 size_t roundup_pow_of_two(size_t size, unsigned int width);
 {
 	if (width == 0) {
 		return 0;
 	}

 	size_t max_width = ((size_t)1) << ((width << 3) - 1);

 	if (size > max_width ) {
 		return max_width;
 	}

 	size_t max = ((size_t)1) << ((sizeof(size_t) << 3) - 1);

 	if ( size > max) {
 		return max;
 	}

 	size_t i = 0;

 	while ((size >> (++i)) != 0){
 		//do nothing
 	}

 	return (((size_t)1) << i);
 }