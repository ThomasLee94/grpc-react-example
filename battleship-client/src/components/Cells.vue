<template>
  <div id="app">
    <h2>"I am a cell"</h2>
  </div>
</template>

<script>
export default {
  name: "Cells",
  props: ["cell"],
  data() {
    return {
      grid: [
        {
          id: 1,
          cellNum: 1
        },
        {
          id: 2,
          cellNum: 2
        },
        {
          id: 3,
          cellNum: 3
        }
      ]
    };
  }
};
</script>

<style scoped>
</style>