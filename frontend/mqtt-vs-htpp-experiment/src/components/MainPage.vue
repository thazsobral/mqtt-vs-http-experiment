<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <p>
      Experimento para estudo e comparação dos protocolos MQTT e HTTP.
    </p>
    <img src="../assets/vs-image.png" alt="versus">
    <div id="chart">
    </div>
    <div>
      <p>Pacotes por minuto</p>
      <p>Tempo de coleta de pacotes</p>
      <p>Qualquer coisa</p>
    </div>
  </div>
</template>

<script>
import ApexCharts from "apexcharts";

export default {
  name: 'HelloWorld',
  props: {
    msg: String
  },
  data () {
    return {
      options: {
        chart: {
          type: 'line',
          height: '500px'
        },
        series: [{
          name: 'sales',
          data: [30,40,35,50,49,60,70,91,125]
        }],
        xaxis: {
          categories: [1991,1992,1993,1994,1995,1996,1997,1998,1999]
        }
      }
    }
  },
  methods: {
    render () {
      var chart = new ApexCharts(document.querySelector("#chart"), this.options)
      chart.render()
    }
  },
  mounted () {
    this.render()
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
