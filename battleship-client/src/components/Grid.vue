<template>
  <div id="app">
    <div v-bind:key="cell.key" v-for="cell in grid">
      <h2>{{cell.title}}</h2>
    </div>
  </div>
</template>

<script>
export default {
  name: "Grid",
  props: ["grid"]
};
</script>

<style scoped>
</style>