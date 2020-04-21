<template>
  <div id="app">
    <div v-bind:key="cell.key" v-for="cell in cells">
      <h2>{{cell.num}}</h2>
      <Cells />
    </div>
  </div>
</template>

<script>
import Cells from "./Cells";
export default {
  name: "Grid",
  props: ["grid"]
};
</script>

<style scoped>
</style>