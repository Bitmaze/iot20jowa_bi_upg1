using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;

namespace AzureFunctions
{
    public static class SaveToCosmos
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("SaveToCosmos")]
        public static void Run(
            [IoTHubTrigger("messages/events", Connection = "IotHubConnection", ConsumerGroup = "cosmos")] EventData message,
                [CosmosDB(
                databaseName: "iot20jowacdb",
                collectionName: "ThingMessage",
                ConnectionStringSetting = "CosmosDB",
                CreateIfNotExists = true
                )]
            out dynamic cosmosdb, ILogger log)
        {
            log.LogInformation($"Trigger aktiverad, meddelande: {Encoding.UTF8.GetString(message.Body.Array)}");
            cosmosdb = Encoding.UTF8.GetString(message.Body.Array);
        }
    }
}