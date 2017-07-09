
let map = c24 => {
  let c16 = c24 % 2 ** 8 >> 3;
  c16 += (c24 >> 8) % 2 ** 8 >> 2 << 5;
  c16 += (c24 >> 16) % 2 ** 8 >> 3 << 11;
  return c16;
}

console.log('0x' + map(Number(process.argv[2])).toString(16).toUpperCase());