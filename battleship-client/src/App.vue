<template>
  <div id="app">
    <Grid v-bind:grid="grid" />
  </div>
</template>

<script>
import Grid from "./components/Grid";

export default {
  name: "App",
  components: {},
  data() {
    return {
      grid: []
    };
  }
};
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
