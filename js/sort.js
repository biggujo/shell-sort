const printArray = (arr) => {
  let n = arr.length;

  arr.forEach((element) => {
    document.write(element + " ");
  });

  document.write("<br>");
};

const sort = (arr) => {
  let n = arr.length;

  for (let gap = Math.floor(n / 2); gap > 0; gap = Math.floor(gap / 2)) {
    for (let i = gap; i < n; i += 1) {
      let temp = arr[i];

      let j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
        arr[j] = arr[j - gap];

      arr[j] = temp;
    }
  }
  return arr;
};

let arr = [12, 34, 54, 2, 3];
document.write("Array before sorting<br>");
printArray(arr);

arr = sort(arr);
document.write("Array after sorting<br>");
printArray(arr);
