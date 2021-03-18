using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace AzureFunctions
{
    public static class GetCosmosData
    {
        [FunctionName("GetCosmosData")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = null)] HttpRequest req,
            [CosmosDB(
            databaseName: "iot20jowacdb",
            collectionName: "ThingMessage",
            ConnectionStringSetting = "CosmosDB",
            SqlQuery = "SELECT * FROM c"
            )]IEnumerable<dynamic> cosmos,
            ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");
            return new OkObjectResult(cosmos);
        }
    }
}

